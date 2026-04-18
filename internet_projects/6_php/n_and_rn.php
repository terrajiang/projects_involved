#!/usr/local/bin/php

<!DOCTYPE html>
<html lang="en">

  <head>
    <meta charset="UTF-8">
    <title>PIC 40A Demo</title>
  </head>

  <body>
    <header>
      <h1>PIC 40A Demo - files using "\n" and "\r\n"</h1>
    </header>

    <main>
      <?php
        $name = 'n_and_rn.txt';


        $file = fopen($name, 'w');
        fwrite($file, "line1\nline2\r\nline3\nline4\r\nline5");
        fclose($file);


        $file = fopen($name, 'r');
        echo '<p>';

        while ($line = fgets($file)) {
          echo $line, '<br>';
          if ($line === "line1\n"  ) { echo 'Roger1<br>'; }
          if ($line === "line2\r\n") { echo 'Roger2<br>'; }
          if ($line === "line3\n"  ) { echo 'Roger3<br>'; }
          if ($line === "line4\r\n") { echo 'Roger4<br>'; }
        }

        echo '</p>';
        fclose($file);


        unlink($name);
      ?>
    </main>

    <footer>
      <hr>
      <small>
        &copy; Sarah Burnett, 2022
      </small>
    </footer>
  </body>

</html>
