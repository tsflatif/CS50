<?php

    // configuration
    require("../includes/config.php"); 
    
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else quote form
        render("quote_form.php", ["title" => "Quote"]);
    }
    
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        if (empty($_POST["symbol"]))
		    apologize("Please enter the stock symbol");
		    
		$stock = lookup($_POST["symbol"]);
		
		if($stock === false)
		    apologize("The stock sybol was not valid");
		else
		    render("../templates/quote_result.php", ["title" => "Quote", 
		    "symbol" => $stock["symbol"], 
		    "name" => $stock["name"], 
		    "price" => $stock["price"]]);    
    }


?>
