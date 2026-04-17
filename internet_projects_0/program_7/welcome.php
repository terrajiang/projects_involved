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
    <title> Shut The Box </title>
		<script src='username.js' defer></script>
		<script src='welcome.js' defer></script>
  </head>

  <body>
    <header>
      <h1> Welcome! Ready to play "Shut The Box"? </h1>
    </header>

    <main>
      <section>
        <h2> Choose a username </h2>

        <p> So that we can post your score(s), please choose a username. </p>

        <fieldset>
          <label for='txt'> Username: </label>
          <input type='text' value='' id='txt'>
          <input type='button' value='Submit' id='sub'>
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

