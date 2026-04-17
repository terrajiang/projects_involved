#!/usr/local/bin/php

<!DOCTYPE html>
<html lang='en'>

  <head>
    <meta charset='UTF-8'>
    <title>Phished</title>
  </head>

  <body>
    <header>
      <h1>HAHAHA</h1>
    </header>

    <main>
      <p>You just got phished!!!
        <br>
        Your password is
        <?php
					if ($_SERVER['REQUEST_METHOD'] === 'POST') {echo $_POST['passwordTyped'];}
				?>
      </p>
    </main>

    <footer>
      <hr>
      <small>
        &copy; Yi-Chong Jiang, 2022
      </small>
    </footer>
  </body>

</html>

