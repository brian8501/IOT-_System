<?php include 'connect.php' ; ?>
<?php
	$result = mysqli_query($con,"SELECT MODE FROM table4 WHERE id=1");
	while($row = mysqli_fetch_array($result))
	{
		$current_MODE = $row['MODE']; 
	}
	if($current_MODE==1){
		//get the post variables from homepage
		$value1 = $_POST['value1'];
		$value2 = $_POST['value2'];
		$value3 = $_POST['value3'];
		$unit = $_POST['unit'];
		
		//update the value of posted column from page in database
		mysqli_query($con,"UPDATE table4 SET HEATER ='{$value1}', FAN='{$value2}', FOG = '{$value3}'
		WHERE id=$unit");
	}
		//go back to the homepage index.php
		header("location: index2.php");
?>