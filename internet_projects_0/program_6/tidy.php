#!/usr/local/bin/php
<?php
  if(isset($_POST['fileUserSelected'])) {
    $file = fopen($_POST['fileUserSelected'], 'r');
    $temp_file = fopen('_0_123_tmp_4_8888_8888.txt', 'w');
    $newName = "tidy_".basename($file);

    while (!feof($file)){
      $line = fgets($file);

      if (substr($line, -2) == '\r\n'){
        fwrite($temp_file, rtrim($line).'\r\n');
      } else if (substr($line, -2) == '\n'){
        fwrite($temp_file, rtrim($line).'\n');
      } else {
        fwrite($temp_file, rtrim($line));
      }
    }

    fclose($file);
    fclose($temp_file);
              
    header('Content-Type: application/octet-stream');
    header('Content-Disposition: attachment; filename='.basename($newName));
    readfile($file);
    
    unlink('_0_123_tmp_4_8888_8888.txt');
    unlink($newName);
    exit();         
  }
?>

<!DOCTYPE html>
<html lang='en'>

  <head>
    <meta charset='UTF-8'>
    <title> PIC 40A Demo </title>
  </head>

  <body>
    <header>
      <h1> PIC 40A Demo - Tidy Trailing Space </h1>
    </header>

    <main>
      <form enctype='multipart/form-data' method='POST' action="<?php echo $_SERVER['PHP_SELF']; ?>">
				<input type='file' name='fileUserSelected' accept='.txt'>
        <br>
				<input type='submit' name='submit'>

			</form>
			
    </main>

    <footer>
      <hr>
      <small>
        &copy; Yi-Chong Jiang, 2022
      </small>
    </footer>
  </body>

</html>
