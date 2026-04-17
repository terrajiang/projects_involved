#!/usr/local/bin/php
<?php 
	header('Content-Type: text/plain; charset=utf-8');

	if (isset($_POST['username'])){
		$username =  $_POST['username']; 
	}

	if (isset($_POST['score'])){
		$score =  $_POST['score']; 
	}

	$file = fopen('scores.txt', 'a');

	if (isset($username) && isset($score)){
		$string = $username.' '.$score."\n";
		fwrite($file, $string);
	}
	
	fclose($file);
?>