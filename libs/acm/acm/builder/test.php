<?php
ini_set('display_errors', '1');

$json = '{"fields":[{"label":"PATIENT DATA PROVA FORM","field_type":"section_break","required":true,"field_options":{"description":"Please fill in all required fields"},"cid":"c1"},{"label":"Patient\'s Name","field_type":"text","required":true,"field_options":{"size":"small"},"cid":"c2"},{"label":"Birthdate","field_type":"date","required":true,"field_options":{},"cid":"c3"},{"label":"Birthplace","field_type":"dropdown","required":true,"field_options":{"options":[{"label":"Italy","checked":false},{"label":"","checked":false}],"include_blank_option":false},"cid":"c4"},{"label":"Medical history","field_type":"file","required":true,"field_options":{},"cid":"c5"},{"label":"Untitled","field_type":"paragraph","required":true,"field_options":{"size":"small"},"cid":"c17"}]}';

foreach (json_decode($json, true) as $section => $js) {
    foreach ($js as $key => $value) {
        print "<hr/>";
        print "Tipo: " . $value["field_type"] . "<br/>";
        print "Etichetta: " . $value["label"] . "<br/>";
        print "Obbligatorio: " . $value["required"] . "<br/>";
        print "Opzioni: " . var_dump($value["field_options"]) . "<br/>";

    }
    //var_dump($value);

}
?>