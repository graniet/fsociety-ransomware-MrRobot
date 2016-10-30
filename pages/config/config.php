<?php
$bdd  = new PDO('mysql:host=localhost;dbname=fsociety','root','');

function get_target(){
    global $bdd;
    $select = $bdd->prepare("SELECT * FROM target WHERE 1");
    $select->execute();
    $fetch = $select->fetch();
    return $fetch;
}
