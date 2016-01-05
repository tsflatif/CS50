<?php

    // configuration
    require("../includes/config.php"); 
    
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        render("sell_form.php", ["title" => "Sell"]);
    }
    
    // if form was submitted
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        if (empty($_POST["stock"]))
		    apologize("Please enter the stock to sell");
		    
		else
		{
		    $id = $_SESSION["id"];
		    $stock = $_POST["stock"];
		    
		    //check if user actually owns the stock
		   		    
		    if(!$shares = query("SELECT shares FROM portfolio WHERE id = $id AND symbol = '$stock'"))
		        apologize("You don't have any shares of this stock");
            
            else
            {
                $value = lookup("$stock");
                $shares = $shares[0]["shares"];
                $price = $value["price"];
                $profit = $shares*$price;
                
                query("DELETE FROM portfolio WHERE id = $id AND symbol = '$stock'");
                query("UPDATE users SET cash = cash + $profit WHERE id = $id");
                query("INSERT INTO history (id, symbol, status, shares, price) 
	 	            VALUES($id, '$stock', 'SELL', $shares, $price)");
                render("../templates/sell_result.php", 
                ["title" => $id, 
		        "value" => $value, 
		        "profit" => $profit]);		        
            }
		}   
    }


?>
