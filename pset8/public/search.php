<?php

    require(__DIR__ . "/../includes/config.php");

    // numerically indexed array of places
    $places = [];

    // Search database for places matching $_GET["geo"]
    
    //trim whitespaces and get $_GET["geo"].
    $param = array_map('trim', preg_split('/( |,|&)/', urldecode($_GET["geo"])));
    
    //query request
    $counts = count($param);
    $request = "SELECT * FROM places WHERE ";
    for ($i = 0; $i < $counts; $i++){
        // look for postal code
        if (is_numeric($param[$i])){
            $request .= 'postal_code LIKE "' . htmlspecialchars($param[$i], ENT_QUOTES) . '%"';
        }
        else {
            $request .= 
                '(place_name  LIKE "' . htmlspecialchars($param[$i], ENT_QUOTES) . '%" OR ' . 
                 'admin_code1 LIKE "' . htmlspecialchars($param[$i], ENT_QUOTES) . '%" OR ' . 
                 'admin_name1 LIKE "' . htmlspecialchars($param[$i], ENT_QUOTES) . '%" OR ' .
                 'country_code LIKE "' . htmlspecialchars($param[$i], ENT_QUOTES) . '%")';
        }
        
        if ($i < ($counts - 1)){
            $request .= " AND ";
        }    
    } 
    
    $places = query($request);
    
    // output places as JSON (pretty-printed for debugging convenience)
    header("Content-type: application/json");
    print(json_encode($places, JSON_PRETTY_PRINT));

?>
