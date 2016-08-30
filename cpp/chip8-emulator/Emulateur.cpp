#include "Emulateur.h"


using namespace std;

Emulateur::Emulateur()
: chip8_fontset {
      0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
      0x20, 0x60, 0x20, 0x20, 0x70, // 1
      0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
      0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
      0x90, 0x90, 0xF0, 0x10, 0x10, // 4
      0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
      0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
      0xF0, 0x10, 0x20, 0x40, 0x40, // 7
      0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
      0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
      0xF0, 0x90, 0xF0, 0x90, 0x90, // A
      0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
      0xF0, 0x80, 0x80, 0x80, 0xF0, // C
      0xE0, 0x90, 0x90, 0x90, 0xE0, // D
      0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
      0xF0, 0x80, 0xF0, 0x80, 0x80  // F
      }
{

}

Emulateur::~Emulateur()
{
    //dtor
}

void Emulateur::initialize()
{
    this->pc = 0x200;
    this->opcode = 0;
    this->I = 0;
    this->_sp = 0;
    this->drawFlag = true;
    this->delay_timer = 0;
    this->sound_timer = 0;

    for(int i = 0; i < 4096; i++)
    {
        this->memoire[i] = 0;
    }
    for(int i = 0; i < 2048; i++)
    {
        this->gfx[i] = 0;
    }
    for(int i = 0; i < 16; i++)
    {
        this->V[i] = 0;
        this->key[i] = 0;
        this->_stack[i] = 0;
    }

    for(int i = 0; i < 80; i++)
    {
        this->memoire[i] = this->chip8_fontset[i];
    }

    srand(time(NULL));
}

void Emulateur::loadGame(string game) throw (logic_error)
{
    ifstream file;
    file.open(game.c_str(), ifstream::in | ifstream::binary | ifstream::ate);

    if(file.is_open())
    {
        this->bufferSize = file.tellg();
        this->buffer = new char[this->bufferSize];
        file.seekg (0, ios::beg);
        file.read (buffer, this->bufferSize);
        file.close();
    }
    else
    {
        throw logic_error("Impossible d'accéder au fichier spécifié");
    }


    for(int i = 0; i < this->bufferSize; i++)
        this->memoire[i+512] = this->buffer[i];

    free(this->buffer);
}

void Emulateur::emulateCycle()
{
    this->opcode = memoire[pc] << 8 | memoire[pc + 1];

    switch(this->opcode & 0xF000)
    {
        case 0x0000:
            switch(this->opcode & 0x00FF)
            {
                case 0x00E0:
                    for(int i = 0; i < 2048; i++)
                        {
                            this->gfx[i] = 0;
                        }
                    drawFlag = true;
                    this->pc += 2;
                break;

                case 0x00EE:
                    this->_sp--;
                    this->pc = this->_stack[_sp];
                    this->pc += 2;
                break;

                default :  break;
            }
        break;

        case 0x1000:
            this->pc = opcode & 0x0FFF;
        break;

        case 0x2000:
            this->_stack[_sp] = pc;
            this->_sp++;
            pc = opcode & 0x0FFF;
        break;

        case 0x3000:
            if(this->V[(opcode & 0x0F00) >> 8] == (opcode & 0x00FF))
                this->pc += 4;
            else
                this->pc += 2;
        break;

        case 0x4000:
            if(this->V[(opcode & 0x0F00) >> 8] != (opcode & 0x00FF))
                this->pc += 4;
            else
                this->pc += 2;
        break;

        case 0x5000:
            if(this->V[(opcode & 0x0F00) >> 8] == this->V[(opcode & 0x00F0) >> 4])
                this->pc += 4;
            else
                this->pc += 2;
        break;

        case 0x6000:
            this->V[(opcode & 0x0F00) >> 8] = (opcode & 0x00FF);
            this->pc += 2;
        break;

        case 0x7000:
            this->V[(opcode & 0x0F00) >> 8] += (opcode & 0x00FF);
            this->pc += 2;
        break;

        case 0x8000:
            switch(opcode &  0x000F)
            {
                case 0x0000:
                    this->V[(opcode & 0x0F00) >> 8] = this->V[(opcode & 0x00F0) >> 4];
                break;

                case 0x0001:
                    this->V[(opcode & 0x0F00) >> 8] |= this->V[(opcode & 0x00F0) >> 4];
                break;

                case 0x0002:
                    this->V[(opcode & 0x0F00) >> 8] &=  this->V[(opcode & 0x00F0) >> 4];
                break;

                case 0x0003:
                    this->V[(opcode & 0x0F00) >> 8] ^= this->V[(opcode & 0x00F0) >> 4];
                break;

                case 0x0004:
                    if( (this->V[(opcode & 0x00F0) >> 4]) > (0xFF - this->V[(opcode & 0x0F00) >> 8]) )
                        V[0xF] = 1;
                    else
                        V[0xF] = 0;

                    this->V[(opcode & 0x0F00) >> 8] += this->V[(opcode & 0x00F0) >> 4];
                break;

                case 0x0005:
					if(V[(opcode & 0x00F0) >> 4] > V[(opcode & 0x0F00) >> 8])
						V[0xF] = 0;
					else
						V[0xF] = 1;
					V[(opcode & 0x0F00) >> 8] -= V[(opcode & 0x00F0) >> 4];
				break;

				case 0x0006:
					V[0xF] = V[(opcode & 0x0F00) >> 8] & 0x1;
					V[(opcode & 0x0F00) >> 8] >>= 1;
				break;

				case 0x0007:
					if(V[(opcode & 0x0F00) >> 8] > V[(opcode & 0x00F0) >> 4])	// VY-VX
						V[0xF] = 0;
					else
						V[0xF] = 1;
					V[(opcode & 0x0F00) >> 8] = V[(opcode & 0x00F0) >> 4] - V[(opcode & 0x0F00) >> 8];
				break;

				case 0x000E:
					V[0xF] = V[(opcode & 0x0F00) >> 8] >> 7;
					V[(opcode & 0x0F00) >> 8] <<= 1;
				break;

				default: break;
            }
            this->pc += 2;
        break;

        case 0x9000:
            if(this->V[(opcode & 0x0F00) >> 8] != this->V[(opcode & 0x00F0) >> 4])
                this->pc += 4;
            else
                this->pc += 2;
        break;

        case 0xA000:
            this->I = (opcode & 0x0FFF);
            this->pc += 2;
        break;

        case 0xB000:
            this->pc = (opcode & 0x0FFF) + this->V[0];
        break;

        case 0xC000:
            this->V[(opcode & 0x0F00) >> 8] = (opcode & 0x00FF) & (rand() % 0xFF);
            this->pc += 2;
        break;

        case 0xD000:
        {
            unsigned short x = V[(opcode & 0x0F00) >> 8];
			unsigned short y = V[(opcode & 0x00F0) >> 4];
			unsigned short height = opcode & 0x000F;
			unsigned short pixel;

			V[0xF] = 0;
			for (int yline = 0; yline < height; yline++)
			{
				pixel = memoire[I + yline];
				for(int xline = 0; xline < 8; xline++)
				{
					if((pixel & (0x80 >> xline)) != 0)
					{
						if(gfx[(x + xline + ((y + yline) * 64))] == 1)
						{
							V[0xF] = 1;
						}
						gfx[x + xline + ((y + yline) * 64)] ^= 1;
					}
				}
			}

			drawFlag = true;
			pc += 2;
        }
        break;

        case 0xE000:
          switch(opcode & 0x00FF)
          {
            case 0x009E:
              if(key[V[(opcode & 0x0F00) >> 8]] != 0)
                this->pc += 4;
              else
                this->pc += 2;
            break;

            case 0x00A1:
                if(key[V[(opcode & 0x0F00) >> 8]] == 0)
                    this->pc += 4;
                else
                    this->pc += 2;
            break;

                default : break;
          }
        break;

        case 0xF000:
            switch(opcode & 0x00FF)
            {
                case 0x0007:
                    this->V[(opcode & 0x0F00) >> 8] = this->delay_timer;
                break;

                case 0x000A:
                    {
                        bool pressed = false;

                        for(int i = 0; i < 16; i++)
                        {
                            if(key[i] != 0)
                            {
                                this->V[(opcode & 0x0F00) >> 8] = i;
                                pressed = true;
                            }
                        }

                        if(!pressed)
                            return;
                    }
                break;

                case 0x0015:
                    this->delay_timer = V[(opcode & 0x0F00) >> 8];
                break;

                case 0x0018:
                    this->sound_timer = V[(opcode & 0x0F00) >> 8];
                break;

                case 0x001E:
                    if(I + V[(opcode & 0x0F00) >> 8] > 0xFFF)
						this->V[0xF] = 1;
					else
						this->V[0xF] = 0;
                    this->I += V[(opcode & 0x0F00) >> 8];
                break;

                case 0x0029:
                    this->I = V[(opcode & 0x0F00) >> 8] * 0x5;
                break;

                case 0x0033:
                     this->memoire[I]     =  V[(opcode & 0x0F00) >> 8] / 100;
                     this->memoire[I + 1] = (V[(opcode & 0x0F00) >> 8] / 10) % 10;
                     this->memoire[I + 2] = (V[(opcode & 0x0F00) >> 8] % 100) % 10;
                break;

                case 0x0055:
                    for(int i = 0x0; i <= ((opcode & 0x0F00) >> 8); i++)
                    {
                        this->memoire[this->I + i] = this->V[i];
                    }

                    I += ((opcode & 0x0F00) >> 8) + 1;
                break;

                case 0x0065:
                    for(int i = 0x0000; i <= ((opcode & 0x0F00) >> 8); i++)
                    {
                        this->V[i] = this->memoire[this->I + i];
                    }
  					I += ((opcode & 0x0F00) >> 8) + 1;
              break;

                default :  break;
            }
            this->pc +=2;
        break;

        default: break;
    }

    if(delay_timer > 0)
        --delay_timer;

    if(sound_timer > 0)
    {
        if(sound_timer == 1)
          cout << "BEEP" << endl;
        --sound_timer;
    }
}

bool Emulateur::update()
{
    return this->drawFlag;
}

unsigned char* Emulateur::getGfx()
{
    return  gfx;
}

void Emulateur::setKeyState(int k, int state)
{
    this->key[k] = state;
}

void Emulateur::setDrawState(bool state)
{
    this->drawFlag = state;
}
