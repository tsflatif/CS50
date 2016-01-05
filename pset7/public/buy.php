<?php

    // configuration
    require("../includes/config.php"); 
    
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        render("buy_form.php", ["title" => "Sell"]);
    }
    
    // if form was submitted
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        if (empty($_POST["stock"])) 
		    apologize("Please enter the stock to buy");
		if (empty($_POST["shares"]) || !preg_match("/^\d+$/", $_POST["shares"]) || ($_POST["shares"] < 0))    
		    apologize("Please enter whole shares of stocks");
		else
		{
		    $symbol = strtoupper($_POST["stock"]);
		    
		    if($stock = lookup($symbol) === false)
		        apologize("This stock does not exist");
		    else
		    {
		        $id = $_SESSION["id"];
		        $shares = $_POST["shares"];
		        $stock = lookup($symbol);
		        $price = $stock["price"];
		        $cash = query("SELECT cash FROM users WHERE id = $id");
		        $cost = $price*$shares;
		        if($cost > $cash[0]["cash"])
		            apologize("You do not have enough cash to buy " . $shares . " shares from " . $stock["name"] . ".");
		        
		        else
		        {
		            query("INSERT INTO portfolio (id, symbol, shares) VALUES($id, '$symbol', $shares) 
		 		    ON DUPLICATE KEY UPDATE shares = shares + $shares");
		 		    query("UPDATE users SET cash = cash - $cost WHERE id = $id");
		 		    query("INSERT INTO history (id, symbol, status, shares, price) VALUES($id, '$symbol', 'BUY', $shares, $price)");
		 		    render("../templates/buy_result.php", ["title" => "Buy", "stock" => $stock, "cost" => $cost, "shares" => $shares]);
		        }    
		    }
		}   
    }


?>
