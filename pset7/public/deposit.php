<?php

    // configuration
    require("../includes/config.php"); 
    
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        render("deposit_form.php", ["title" => "Sell"]);
    }
    
    // if form was submitted
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        if (empty($_POST["amount"]))
		    apologize("Please enter how much you want to deposit");
		    
		else
		{
		    $id = $_SESSION["id"];
		    $amount = $_POST["amount"];
		    
		    //check if user actually owns the stock
		   		    
		    if($amount <= 0 || !is_numeric($amount))
                apologize("Not a valid number");
            else
            {
                query("UPDATE users SET cash = cash + $amount WHERE id = $id");
		 	    query("INSERT INTO history (id, status, price) VALUES($id, 'DEPOSIT', $amount)");
		 	    render("../templates/deposit_result.php", ["title" => "Deposit", "amount" => $amount]);    	        
            }
		}   
    }


?>
