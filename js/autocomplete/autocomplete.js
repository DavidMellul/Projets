$(document).ready( function() {
	var listeResultats = [];
	var recherche = '';
	var compteur = 0;


	$('#results').hover(function() {
		$('#results p').each( function() {
			$(this).hover( function() {
				$(this).addClass('autocomplete_result');
			},
			function() {
				$(this).removeClass('autocomplete_result');
			});
		});
	});

	$('#results').hover(function() {
		$('#results > p').each( function() {
			$(this).click( function() {
				$('#search').val($(this).text());
				listeResultats = [];
				$('#results').empty();	
			});
		});
	});

	$('#search').keyup( function(e) {
		if(!$('#search').val())
			$('#results').empty();
		else
		{
			if(e.which == 8 || (e.which >= 65 && e.which <= 90))
				{
					$('#results').empty();
					listeResultats = [];
					recherche = $('#search').val().toUpperCase();
					var requete;

					if(window.XMLHttpRequest)
						requete = new XMLHttpRequest();
					else
						requete = new ActiveXObject('Microsoft.XMLHTTP');

					requete.onreadystatechange = function() {
						if(requete.readyState == 4 && requete.status == 200) {
							if(requete.responseText)
								listeResultats = requete.responseText.split(' ').filter(function(v){return v!==''});
							else 
							{
								listeResultats.push('<p>Aucun resultat trouvé.</p>');
								recherche = '';
							}

							compteur = 1;
							for(var i = 0; i < listeResultats.length; i++)
								$('#results').append('<p><span>'+recherche+'</span>'+listeResultats[i].substr(recherche.length,listeResultats[i].length)+'</p>');
							
							$('#results > p').removeClass('autocomplete_result');
							$('#results > p:nth-child('+compteur+')').addClass('autocomplete_result');
						}
					};

					requete.open('GET','script.php?q='+recherche,true);
					requete.send();
				}	
			else
			 {
			 	if(listeResultats.length > 0 )
			 	{
			 		 	switch(e.which) 
			 			{
							case 13:  
										$('#search').val(listeResultats[compteur-1]);
										listeResultats = [];
										$('#results').empty();
										compteur = 0;
									break;
							case 38: 
									if(compteur > 1)
									 	compteur--; 
									 break;
							case 40:  
									if(compteur < listeResultats.length)
										compteur++; 
									break;
						}
				}
				$('#results > p').removeClass('autocomplete_result');
				$('#results > p:nth-child('+compteur+')').addClass('autocomplete_result');
			}
	}
	});
});