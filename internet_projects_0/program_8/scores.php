#!/usr/local/bin/php
<?php
  session_save_path(__DIR__.'/sessions/');
  session_name('login_w_password');
  session_start();

  $loggedin = isset($_SESSION['loggedin']) && $_SESSION['loggedin'];

  if(!$loggedin){
      header('Location: login.php');
      exit;
  }
?>

<!DOCTYPE html>

<html lang='en'>
	<head>
		<meta charset='UTF-8'>
		<title>Shut The Box</title>
		<script src='scores.js' defer></script>
	</head>

	<body>
		<header>
			<h1>Shut The Box</h1>
		</header>

		<main>
			<section>
				<h2>Scores</h2>

				<p>Well done! Here are the scores so far...</p>

				<p></p>


				<fieldset>
					<input type='button' value='PLAY AGAIN!!!'>
				</fieldset>

				<fieldset>
					<input type='button' value='Force update / start updating'>
					<input type='button' value='Stop updating'>
				</fieldset>

			</section>
		</main>


		<footer>
			<hr>
			<small>
				&copy; Yi-Chong Jiang, 2022
			</small>
		</footer>

	</body>

</html>