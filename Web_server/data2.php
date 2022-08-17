<?php 
header("Content-type: text/json");
include 'connect.php';
$result = mysqli_query($con,"SELECT TEMP,HUMI,TIME FROM dulieu");
if (!$result) {
    die(mysqli_error($conn));
}
$ret = array();
while ($row = mysqli_fetch_array($result)){
        $current_time = strtotime($row['TIME'])*1000;
		$current_humi = intval($row['HUMI']);
        $y = rand(0, 100);          
        $ret[] = array($current_time, $current_humi);     
}
    echo json_encode($ret, JSON_NUMERIC_CHECK);
?>