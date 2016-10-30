<?php
ini_set('display_errors', 'on');
require_once('config/config.php');

if(isset($_GET['insert']) && isset($_GET['nb_file']) && !empty($_GET['nb_file']) && is_numeric($_GET['nb_file'])){
    $address_ip = $_SERVER['REMOTE_ADDR'];
    $arch = "x64";
    $nb_file = $_GET['nb_file'];
    $day = date("d")+1;
    $month = date('m');
    $year = date('y');
    $hours = date('h:i:s');
    $date = $month.'/'.$day.'/'.$year.' '.$hours;
    echo $address_ip;
    $select = $bdd->prepare("SELECT * FROM target WHERE ip_adress = :ip_addr");
    $select->bindParam(':ip_addr', $address_ip);
    $select->execute();
    if($select->rowCount() < 1){
	var_dump($select->fetch());
	$insert = $bdd->prepare("INSERT INTO target(ip_adress,nb_file,system_arch,date_time) VALUES(:ip_addr,:nb_file,:arch,:date_time)");
	$insert->bindParam(':ip_addr', $address_ip);
	$insert->bindParam(':nb_file', $nb_file);
	$insert->bindParam(':arch', $arch);
	$insert->bindParam(':date_time', $date);
	$insert->execute();
	echo "inserted";
    }
}
else{
    echo "get not set";
}
