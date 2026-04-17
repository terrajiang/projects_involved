#!/usr/local/bin/php

<!DOCTYPE html>
<html lang='en'>

  <head>
    <meta charset='UTF-8'>
    <title>Interesting</title>
  </head>

  <body>
    <header>
      <h1>Welcome to site with interesting content</h1>
    </header>

    <main>
      <section>
        <h2>Welcome</h2>
        <p>Welcome
          <?php
						if ($_SERVER['REQUEST_METHOD'] === 'POST') {echo $_POST['usernameTyped'];}
					?>!!!
          <br>
          (We didn't check the password because this is a demo of something else.)
        </p>
      </section>

      <section>
        <h2>Recent posts by users</h2>

        <p>
          NiceGuy666 said, "check out my
          <a href='holiday1.html' target='_blank' rel='opener'>holiday</a>
          <a href='holiday2.html' target='_blank' rel='opener'>pictures</a>!"
        </p>
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
