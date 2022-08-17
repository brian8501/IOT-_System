<?php include 'connect.php' ; ?>
<?php
		$result = mysqli_query($con,"SELECT MODE FROM table4 WHERE id=1");
		while($row = mysqli_fetch_array($result))
		{
			$current_MODE = $row['MODE']; 
		}
		if($current_MODE==1){
		//get the post variables from homepage
		$value = $_POST['value'];
		$unit = $_POST['unit'];
		$column = $_POST['column'];
		
		//update the value of posted column from page in database
		mysqli_query($con,"UPDATE table4 SET $column = '{$value}' WHERE id=$unit");
		}
		//go back to the homepage index.php
		header("location: index2.php");
?>