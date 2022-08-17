  <?php 
   session_start();
	if(!isset($_SESSION["access"])){
	header("Location: index.php");}
 ?>
<?php include 'connect.php' ; ?>
<?php 
$page = $_SERVER['PHP_SELF'];
$sec = "1000";
?>
<html>
    <head>
		<meta charset="UTF-8">
       <meta http-equiv="refresh" content="<?php echo $sec?>;URL='<?php echo $page?>'">
	   <title>IoT with ESP8266</title>
	   <link rel="stylesheet" href="./style.css" type="text/css"/>
	   <link rel="icon" href="image/page2-icon.jpg"> 	
	   <script src="https://code.highcharts.com/highcharts.js"></script>
	   <script
		src="https://code.jquery.com/jquery-3.3.1.min.js"
		integrity="sha256-FgpCb/KJQlLNfOu91ta32o/NMZxltwRo8QtmkMRdAu8="
		crossorigin="anonymous"></script>
	   <script src="https://code.highcharts.com/modules/exporting.js"></script>
	   <script src="https://code.highcharts.com/modules/export-data.js"></script>
	   <script type="text/javascript" ></script>
    </head>
    <body>
		<div class="wrapper">
		<div class="header">
			<a href="http://vuonganhiot.000webhostapp.com/index2.php" target="_blank"><img src="image/home-warm.png"  id="img-home" alt="HOME"/></a>
			<div id="txt-name">Hệ Thống Lò Sưởi Và Tạo Ẩm Tự Động Trong Nhà</div>
			<div id="txt-contact">Liên hệ:</div>
			<a href="http://facebook.com/vuonganhdo95" target="_blank"><img src="image/contact-fb.png" id="img_contact" alt="Contact FB" /></a>
			<a href="http://facebook.com/dovuonganh95" target="_blank"><img src="image/contact-zl.png" id="img_contact" alt="Contact ZL" /></a>
			<div class="clr"></div>
		</div>
		<div class="left">
			
			<div id="showtemp">
				<img src="image/temp.png" alt="Temperature" id="image_temp">
				<div id="txt-show1">
					<?php
						$result = mysqli_query($con,"SELECT * FROM dulieu WHERE id=(SELECT MAX(id) FROM dulieu)"); 
						while($row = mysqli_fetch_array($result)){
						echo $row['TEMP'] . "°C";
						}
					?></br></div>
				<div class="clr"></div>
				<div id="txt-show2">
				<?php
					$result = mysqli_query($con,"SELECT * FROM dulieu WHERE TEMP=(SELECT MAX(TEMP) FROM dulieu)"); 
					while($row = mysqli_fetch_array($result)){
					echo "Temperature Max: " . $row['TEMP'] . "°C";
					}
				?></br></div>
				<div id="txt-show3">
					<?php
						$result = mysqli_query($con,"SELECT * FROM dulieu WHERE TIME=(SELECT MAX(TIME) FROM dulieu)"); 
						while($row = mysqli_fetch_array($result)){
						echo "Last update: " . $row['TIME'];
						}
					?></br></div>
			</div>
			<div class="clr"></div>
			<div id="showhumi">
				<img src="image/humi.png" alt="Humidity" id="image_humi">
				<div id="txt-show1">
					<?php
						$result = mysqli_query($con,"SELECT * FROM dulieu WHERE id=(SELECT MAX(id) FROM dulieu)"); 
						while($row = mysqli_fetch_array($result)){
						echo $row['HUMI'] . "%";
						}
					?></br></div>
				<div class="clr"></div>
				<div id="txt-show2">
					<?php
						$result = mysqli_query($con,"SELECT * FROM dulieu WHERE HUMI=(SELECT MAX(HUMI) FROM dulieu)"); 
						while($row = mysqli_fetch_array($result)){
						echo "Humidity Max: " . $row['HUMI'] . "%";}
					?></br></div>
				<div id="txt-show3">
					<?php
						$result = mysqli_query($con,"SELECT * FROM dulieu WHERE TIME=(SELECT MAX(TIME) FROM dulieu)"); 
						while($row = mysqli_fetch_array($result)){
						echo "Last update: " . $row['TIME'];
						}
					?></br></div>
			</div>
			<div class="clr"></div>
			<div id="weether">
				<div id="cont_9717b5c3d1215f81a90fcebc13e090a5"><script type="text/javascript" async src="https://www.theweather.com/wid_loader/9717b5c3d1215f81a90fcebc13e090a5"></script></div>
			</div>
		</div>
		<div class="content">
		<h1><marquee behavior="alternate" width="10%">_★_</marquee>CONTROL SINGLE DEVICE</marquee></h1>
		<div id="control">
		<?php
			echo 
			"
			<table border='4' id='table'>
			<tr>
			<th style='width:260px'>HEATER</th>
			<th style='width:260px'>FAN</th>
			<th style='width:260px'>FOG</th>
			</tr>
			";
			$result = mysqli_query($con,"SELECT * FROM table4"); 
			while($row = mysqli_fetch_array($result)) 
			{
				echo "<tr>";
					$unit_id = $row['id']; 
					$column_HEATER = "HEATER";  
					$current_HEATER = $row['HEATER']; 
					$column_FOG = "FOG";  
					$current_FOG = $row['FOG']; 
					$column_FAN = "FAN";  
					$current_FAN = $row['FAN']; 
				echo 
				"
				<td>
				<form id='heater_form' action= database.php method='post'>
				<input id='heater_text_box' type='number' name='value' value=$current_HEATER min='0' max ='1'> 
				<input type='hidden' name='unit' value=$unit_id >
				<input type='hidden' name='column' value=$column_HEATER >
				<input id='submit_button' type= 'submit' name= 'change_but' style='text-align:center' value='ON/OFF'>
				</form>
				</td>
				";

				echo 
				"
				<td>
				<form  id='fan_form' action= database.php method='post'>
				<input id='fan_text_box' type='number' name='value' value=$current_FAN min='0' max ='1' maxleght='1'> 
				<input type='hidden' name='unit' value=$unit_id >
				<input type='hidden' name='column' value=$column_FAN >
				<input id='submit_button' type= 'submit' name= 'change_but' style='text-align:center' value='ON/OFF'>
				</form>
				</td>
				";
				echo 
				"
				<td>
				<form id='fog_form' action= database.php method='post'>
				<input id='fog_text_box' type='number' name='value' value=$current_FOG min='0' max='1'> 
				<input type='hidden' name='unit' value=$unit_id >
				<input type='hidden' name='column' value=$column_FOG >
				<input id='submit_button' type= 'submit' name= 'change_but' style='text-align:center' value='ON/OFF'>
				</form>
				</td>
				";					
			}
			echo "</tr>"; 
			echo "</table>";  
		?>
		<?php 
            
		    $result = mysqli_query($con,"SELECT * FROM table4");
			while($row = mysqli_fetch_array($result)) 
			{
			     $current_HEATER = $row['HEATER']; 
				 if($current_HEATER == 0) 
				 {
					echo"   <img id='image_heater' onclick='change_image_heater()' src='image/heater_off.png' > ";
				 }
				 else
				 {
					echo"   <img id='image_heater' onclick='change_image_heater()' src='image/heater_on.png' > ";
				 }
			    $current_FAN = $row['FAN']; 
				 if($current_FAN == 0) 
				 {
					echo"<img id='image_fan' onclick='change_image_fan()' src='image/fan_off.png'>";
				 }
				 else
				 {
					echo"<img id='image_fan' onclick='change_image_fan()' src='image/fan_on.png'>";
				 }
			     $current_FOG = $row['FOG']; 
				 if($current_FOG == 0) 
				 {
				 echo"<img id='image_fog' onclick='change_image_fog()' src='image/fog_off.png'>";
				 }
				 else
				 {
				echo"<img id='image_fog' onclick='change_image_fog()' src='image/fog_on.png'>";
				 } 
			}
			?> 	 
			<script>
				function change_image_heater() {
				var image = document.getElementById('image_heater');
				if (image.src.match("image/heater_on.png")) 
				{
					image.src = "image/heater_off.png";
					document.getElementById("heater_text_box").value = 0;
				} 
				else 
				{
					image.src = "image/heater_on.png";
					document.getElementById("heater_text_box").value = 1;
				}
				document.getElementById("heater_form").submit();
				}
				function change_image_fan() {
				var image = document.getElementById('image_fan');
				if (image.src.match("image/fan_on.png")) {
					image.src = "image/fan_off.png";
					document.getElementById("fan_text_box").value = 0;
				} else {
					image.src = "image/fan_on.png";
					document.getElementById("fan_text_box").value = 1;
				}
				document.getElementById("fan_form").submit();
				}
				function change_image_fog() {
				var image = document.getElementById('image_fog');
				if (image.src.match("image/fog_on.png")) {
					image.src = "image/fog_off.png";
					document.getElementById("fog_text_box").value = 0;
				} else {
					image.src = "image/fog_on.png";
					document.getElementById("fog_text_box").value = 1;
				}
				document.getElementById("fog_form").submit();
				}
			</script>	
	</div>
	<div class="clr"></div>
	<h1><marquee behavior="alternate" width="10%">_★_</marquee>CONTROL MULTIPLE DEVICE & SETTUP</h1>
	<div id="settup">
		<form action=database2.php method="post">
			<input type="hidden" name="unit" value="1">
			<input type="hidden" name="value1" value="1">
			<input type="hidden" name="value2" value="1">
			<input type="hidden" name="value3" value="1">
			<input id="img-start" type="image" src="image/on_all.png" alt="Submit">
		</form>
		<form action=database2.php method="post">
			<input type="hidden" name="unit" value="1">
			<input type="hidden" name="value1" value="0">
			<input type="hidden" name="value2" value="0">
			<input type="hidden" name="value3" value="0">
			<input id="img-stop" type="image" src="image/off_all.png" alt="Submit">
		</form>
	<?php
	$result = mysqli_query($con,"SELECT * FROM table4");
	while($row = mysqli_fetch_array($result))
	{
		$unit_id = $row['id']; 
		$column_TEMPSET = "TEMPSET";
		$current_TEMPSET = $row['TEMPSET'];
		$column_HUMISET = "HUMISET";
		$current_HUMISET = $row['HUMISET'];	
		$current_MODE = $row['MODE']; 
		$column_MODE = "MODE";
		echo "
		<form id='setmode_form' action=database3.php method='post'>
		<input type='hidden' name='unit' value=$unit_id >
		<input type='hidden' name='column' value=$column_MODE >
		<input id='mode_value' type='hidden' name='value' value='$current_MODE'>
		</form>";
		if($current_MODE == 0) 
				 {
					echo"   <img id='img-mode' onclick='change_image_mode()' src='image/manual.png' >";
				 }
				 else
				 {
					echo"   <img id='img-mode' onclick='change_image_mode()' src='image/auto.png' >";
				 }
		echo "<div id='txt-sethumi'>
			<form id='sethumi_form' action= database3.php method='post'>
			<input id='humi_text_box' type='number' name='value' value=$current_HUMISET min='40' max ='80'>
			<input type='hidden' name='unit' value=$unit_id >
			<input type='hidden' name='column' value=$column_HUMISET >
			<input id='submit_button1' type= 'submit' name= 'change_but' value='CHANGE SET HUMI'>
			</form>
			<form id='settemp_form' action= database3.php method='post'>
			<input id='temp_text_box' type='number' name='value' value=$current_TEMPSET min='17' max='32'>
			<input type='hidden' name='unit' value=$unit_id >
			<input type='hidden' name='column' value=$column_TEMPSET >
			<input id='submit_button1' type= 'submit' name= 'change_but' value='CHANGE SET TEMP'>
			</form>
			</div>";
	}
	?>
	<script>
		function change_image_mode() {
		var image = document.getElementById('img-mode');
		if (image.src.match("image/auto.png")) 
		{
			image.src = "image/manual.png";
			document.getElementById("mode_value").value = 0;
		} 
		else 
		{
			image.src = "image/auto.png";
			document.getElementById("mode_value").value = 1;
		}
		document.getElementById("setmode_form").submit();
		}
	</script>
	</div>
	<div class="clr"></div>
	<h1><marquee behavior="alternate" width="10%">_★_</marquee>CHART FOR TEMPERATURE & HUMIDITY</h1>
	<div id="chartupdate"> </div>
	<div class="clr"></div>
<script type="text/javascript">
	$(document).ready(function() {
    var options = {
        chart: {
            renderTo: 'chartupdate',
            type: 'spline',
        },
		title: {
			text: 'Temperature and Humidity Chart'
		  },
		xAxis: {
			type: 'datetime',
			  tickPixelInterval: 100
		},
		yAxis: {
			title: {
			text: 'Value'
		},
		plotLines: [{
			value: 0,
			width: 1,
			color: '#808080'
		}]},
		time: {
			timezone: 'Asia/Bangkok'
		},
		tooltip: {
			formatter: function () {
			  return '<b>' + this.series.name + '</b><br/>' +
				Highcharts.dateFormat('%Y-%m-%d %H:%M:%S', this.x) + '<br/>' +
				Highcharts.numberFormat(this.y, 2);
			}
		  },
        series: [{name: 'Temperature',},{name: 'Humidity',}]
    };
    $.getJSON('data.php', function(data1) {
        options.series[0].data = data1;
		var chart = new Highcharts.Chart(options);
    });
	$.getJSON('data2.php', function(data2) {
        options.series[1].data = data2;
		var chart = new Highcharts.Chart(options);
    });
	
});
</script>
	</div>
	<div class="clr"></div>
	<div class="footer">
		<div id="txt-footer">
			<h2>Design by Vuong Anh Do</h2>
			<h2>Email: vuonganh1106@gmail.com</h2>
		</div>
		<div id="txt-footer2">
			<h2 id="11">University of Transport and Communications</h2>
			<h2 id="12">Class: TĐH & ĐK - K55</h2>
		</div>
		<div id="logout">
			<a href="logout.php"><h3 id="txt-logout">Logout</h3><img id="img-logout" src="image/logout.png"/></a>;
		</div>
		<div class="clr"></div>
	</div>
	</div>
</body>
</html>




