<?php include 'connect.php' ; ?>
<?php
		foreach($_REQUEST as $key => $value)
		{
			if($key =="mode")
			{
				$mode = $value;
			}
			if($key == "tempset")
			{
				$tempset  = $value; 
			}
			if($key == "humiset")
			{
				$humiset  = $value; 
			}
			if($key =="heat")
			{
				$heat = $value;
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
			    mysqli_query($con,"INSERT INTO dulieu(TEMP,HUMI,TIME) VALUES ($temp,$humi,NOW())");
			}
		}
		if ($mode == '1')
		{
			mysqli_query($con,"UPDATE table3 SET HEATER = $heater WHERE id=1");
			mysqli_query($con,"UPDATE table3 SET FAN = $fan WHERE id=1");
			mysqli_query($con,"UPDATE table3 SET FOG = $fog WHERE id=1");
		}
		if ($mode == '3')
		{
			mysqli_query($con,"UPDATE table4 SET TEMPSET = $tempset WHERE id=1");
			mysqli_query($con,"UPDATE table4 SET HUMISET = $humiset WHERE id=1");
		}
		$result1 = mysqli_query($con,"SELECT * FROM table4");
		while($row = mysqli_fetch_array($result1))
		{
			if($row['id'] == $unit)
			{
				$get_heater = $row['HEATER']; 
				$get_fan = $row['FAN'];
				$get_fog = $row['FOG'];
				$get_tempset = $row['TEMPSET'];
				$get_humiset= $row['HUMISET'];
		      echo "#START-HEATER=$get_heater-FAN=$get_fan-FOG=$get_fog"; 
		   }
		
			}
?>