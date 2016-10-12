# Autocomplete

Il s'agit d'un script fait en Javascript (JQUERY / AJAX) permettant d'auto-compléter une saisie de l'utilisateur d'après une liste rapatriée d'un
script php. On peut naviguer entre les résultats avec les fléches directionnelles et se servir de [ENTER] ou de la souris pour confirmer.

<b>Pour l'utiliser :</b>
  1. Créer un input :
  ```javascript
$(function(){
  $('div').html('I am a div.');
});
```
  2. Créer une div pour les résultats : 
  ```javascript
    <div id="results"></div>
    ```
