<?php include 'connect.php' ; ?>
<?php
		foreach($_REQUEST as $key => $value)
		{
			if($key =="unit")
			{
				$unit = $value;
			}
			if($key == "mode")
			{
				$mode  = $value; 
				mysqli_query($con,"UPDATE table4 SET MODE = $mode WHERE id=$unit");
			}
			if($key =="heater")
			{
				$heater = $value;
			}
			if($key =="fan")
			{
				$fan = $value;
			}
			if($key =="fog")
			{
				$fog = $value;
			}
			if($key =="temp")
			{
			    $temp = $value;
			    
			}
			if($key =="humi")
			{
				$humi = $value;
				//mysqli_query($con,"SET time_zone = +07:00");
				mysqli_query($con,"INSERT INTO dulieu(TEMP,HUMI,TIME) VALUES ($temp,$humi,NOW())");
			}
		}
		if ($mode == '1')
		{
			mysqli_query($con,"UPDATE table4 SET HEATER = $heater WHERE id=$unit");
			mysqli_query($con,"UPDATE table4 SET FAN = $fan WHERE id=$unit");
			mysqli_query($con,"UPDATE table4 SET FOG = $fog WHERE id=$unit");
		}
		$result = mysqli_query($con,"SELECT * FROM table4");
		while($row = mysqli_fetch_array($result))
		{
			if($row['id'] == $unit)
			{
				$get_heater = $row['HEATER']; 
				$get_fan = $row['FAN'];
				$get_fog = $row['FOG'];
				$get_update = $row['MODE'];
				$get_temp_set = $row['TEMPSET'];
				$get_humi_set = $row['HUMISET'];
		      echo "#START-HEATER=$get_heater-FAN=$get_fan-FOG=$get_fog-TEMPSET=$get_temp_set-HUMISET=$get_humi_set-UPDATE=$get_update-#END\r\n\r\n"; 
		   }
		}
?>