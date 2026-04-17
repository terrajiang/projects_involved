#!/usr/local/bin/php
<?php
  header('Content-Type: text/plain; charset=utf-8');

  $file = fopen('windows.txt', 'r');

  while ($line = fgets($file)) {
    if ($line === "Here is a line with 2 spaces after it.  \r\n") {
      echo "Roger! 2\n";
    }
    if ($line === "Here is a line with 1 spaces after it. \r\n") {
      echo "Roger! 1\n";
    }
  }

  fclose($file);
?>
