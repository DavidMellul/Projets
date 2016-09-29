<?php

$voitures = array(
   "Renault" =>  array(
                       "Twingo" => array("-1", "9999€","-1"),
                       "Clio" => array("-1", "11999€", "-1"),
                       "Mégane" => array("-1", "14999€", "-1"),
                       "Laguna" => array("-1", "17999€", "-1")
                     ),
   "Peugeot" =>  array(
                     "107" => array("-1", "8995€", "-1"),
                     "207" => array("-1", "11995€", "-1"),
                     "308" => array("-1", "14995€", "-1"),
                     "508" => array("-1", "17995€", "-1")
                   ),
   "Citroen" => array(
                   "C1" => array("-1", "7990€", "-1"),
                   "C3" => array("-1", "10990€", "-1"),
                   "C4" => array("-1", "13990€", "-1"),
                   "C5" => array("-1", "16990€", "-1")
                 ),
   "Volkswagen" => array(
     "Lupo" => array("", "6985€", ""),
     "Polo" => array("", "9985€", ""),
     "Golf" => array("", "12985€", ""),
     "Passat" => array("", "15985€", "")
   )
  );
?>

<!DOCTYPE HTML>
<html>
  <head>
      <meta charset="UTF-8" />
      <title>Formulaire de saisie</title>
  </head>
  <body>
    <h1 style="text-align:center">Formulaire de saisie</h1>
    <table style="border-style:solid;">
        <tr>
          <th>Marque</th>
          <th>Modèle</th>
          <th>Modifier modèle</th>
          <th>Prix</th>
          <th>Modifier prix</th>
        </tr>
        <?php
          $compteur = 0;
          foreach ($voitures as $marque => $data) {
            echo "<tr>";
            echo "<td>".$marque."</td>";
            echo "</tr>";
            foreach($data as $modele => $content )
            {
              echo "<tr>";
              echo "<td></td>";
              echo "<td>".$modele."</td>";
              foreach($content as $str)
              {
                if($str != "-1")
                  echo "<td>".$str."</td>";
                else
                {
                  $compteur++;
                  echo "<td>
                          <input type=\"text\" name=\"modifier".$compteur."\" />
                        </td>";
                }
              }
              echo "</tr>";
            }
          }
         ?>
    </table>
    <form method="POST">
      <label for="marque">Marque :</label>
      <select name="marque">
        <option value="Renault">Renault</option>
        <option value="Peugeot">Peugeot</option>
        <option value="Citroen">Citroen</option>
        <option value="Volkswagen">Volkswagen</option>
      </select>
      <label for="modele">Nouveau modèle :</label>
        <input type="text" name="modele" />
      <label for="prix">Nouveau prix :</label>
        <input type="text" name="prix" />
        <input type="submit" value="Tout valider" />
      </form>
  </body>
</html
