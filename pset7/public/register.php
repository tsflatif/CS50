<?php

    // configuration
    require("../includes/config.php");

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("register_form.php", ["title" => "Register"]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        if (empty($_POST["username"]))
		    apologize("You must provide username");

	    else if (empty($_POST["password"]))
		    apologize("You must provide password");

	    else if (empty($_POST["confirmation"]))
		    apologize("You must confirm your password");

	    else if ($_POST["confirmation"] != $_POST["password"])
		    apologize("Your passwords do not match!");

	// Check if username is unique 
	    $query = query("INSERT INTO users (username, hash, cash) VALUES(?, ?, 10000.00)", $_POST["username"], crypt($_POST["password"]));

	    if( $query === false)
		    apologize( 'Username already exists'); 
	    else
	    {
		    $rows = query("SELECT LAST_INSERT_ID() AS id");
		    $id = $rows[0]["id"];
		    $_SESSION["id"] = $id;
		    redirect("/");
	    }	
	
    }

?>
