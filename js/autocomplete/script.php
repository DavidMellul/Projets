<?php
	function str_starts_with($haystack, $needle)
	{
    	return strpos($haystack, $needle) === 0;
	}

	if(isset($_GET['q']))
	{
		$mot = $_GET['q'];
		$liste = array("david", "léa", "roxanne", "pierre", "manon", "emma", "jade", "léna", "camille", "zoé", "anna", "rose", "lucie", "inès", "mila", "lola", "ambre", "élise", "julia", "romane", "juliette", "clara", "eva", "maëlys", "margaux", "mathilde", "léana", "charlotte", "lana", "léonie", "agathe", "éléna", "lou", "mia", "lily", "louna", "nina", "capucine", "jeanne", "soline", "olivia", "maëlle", "clémence", "lina", "anaïs", "lilou", "eden", "sarah", "noémie", "théa", "lucas", "hugo", "jules", "raphaël", "léo", "louis", "gabriel", "arthur", "ethan", "nathan", "paul", "gabin", "maël", "maxime", "liam", "martin", "timéo", "tom", "baptiste", "clément", "sacha", "théo", "antoine", "axel", "robin", "mathis", "enzo", "nolan", "maxence", "noé", "aaron", "victor", "valentin", "malo", "noah", "thomas", "mathéo", "alexis", "marius", "alexandre", "simon", "adam", "eliott", "évan", "mathys", "naël", "louka", "antonin", "lenny", "matteo",);
		$retour = array();
		for($i = 0; $i < count($liste); $i++)
		{
			if(str_starts_with(strtoupper($liste[$i]), $mot) == true)
				array_push($retour,$liste[$i]);
		}
		echo implode(' ',$retour);
	}
	
?>
