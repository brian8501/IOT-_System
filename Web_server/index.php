<!DOCTYPE html>
<html lang="en" >
	<head>
	<meta charset="UTF-8">
    <meta http-equiv="refresh" content="<?php echo $sec?>;URL='<?php echo $page?>'">
	<title>Đăng nhập - IOT with ESP</title>
	<link rel="icon" href="./image/Home-icon.png">  
	<link rel="stylesheet" href="css/style.css">
	<link rel='stylesheet' href='http://netdna.bootstrapcdn.com/bootstrap/3.0.2/css/bootstrap.min.css'>
    </head>
    <body>
	<div class="wrapper">
    <form class="form-signin" action="check_login.php" method="post"  id='login_form'>       
      <h2 class="form-signin-heading">Đăng nhập hệ thống</h2>
      <input type="text" class="form-control" name="user_name" placeholder="Username" required="" autofocus="" />
      <input type="password" class="form-control" name="password" placeholder="Password" required=""/>      
	  <?php  if(isset($_GET['error'])) : ?>
		<div id="login_error_msg"> <?php echo $_GET['error']; ?> </div><br/>
	  <?php endif; ?>
      <button class="btn btn-lg btn-primary btn-block" type="submit" name="submit">Đăng nhập</button>   
    </form>
	</div>
	</body>
</html>
