<?php

    // configuration
    require("../includes/config.php"); 
    
    $id = $_SESSION["id"];
    // retrieve all share info of the user
    $rows = query("SELECT id, symbol, shares FROM portfolio WHERE id = $id");
    
    //placeholder array
    $positions = [];
    
    foreach ($rows as $row)
    {
        $stock = lookup($row["symbol"]);
        if ($stock !== false)
        {
            $positions[] = [
            "name" => $stock["name"],
            "price" => $stock["price"],
            "shares" => $row["shares"],
            "symbol" => $row["symbol"],
            "total" => sprintf("%.2f", $row["shares"]*$stock["price"])
        ];
        }
    }
    
    $user = query("SELECT * FROM users WHERE id = $id");

    // render portfolio
    render("portfolio.php", ["title" => "Portfolio", "positions" => $positions, "users" => $user]);

?>
