<?php include 'connect.php' ; ?>

<?php 

   //check if form was submitted
  if(isset($_POST["submit"])) 
  {     
		// username và password được gửi từ form đăng nhập
		$myusername=$_POST['user_name'];
		$mypassword=$_POST['password'];
		//$sql="SELECT * FROM dangnhap WHERE username='$myusername' and password='$mypassword'";
		$result = mysqli_query($con,"SELECT * FROM dangnhap WHERE username='$myusername' and password='$mypassword'");
		$count= mysqli_num_rows($result); 
		// nếu tài khoản trùng khớp thì sẽ trả về giá trị 1 cho biến $count
		if($count==1){
		session_start();
        $_SESSION["access"] = "OK";   
        header("Location: index2.php");
        exit();
		}
		else
		{
			$error = "Username hoặc Password chưa đúng!";
			header( "Location: index.php?error=" . urlencode($error) );
			exit();
		}
    }
?>


