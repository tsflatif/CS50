<div>
	<div id="message">
		<?php
			print("Hello, ". $users[0]["username"] .". Your current balance is " . sprintf("%.2f",$users[0]["cash"]).".");
		?>
	</div>
	</br>
    <table id="overview" style="width:100%">
        <tr>
            <th>Symbol</th>
            <th>Name</th>
            <th>Shares</th>
            <th>Price</th>
            <th>Total</th>
        </tr>
                
						  
			<?php foreach ($positions as $position): ?>

				<tr>
                    <td align="left"><?= $position["symbol"] ?></td>
                    <td align="left"><?= $position["name"] ?></td>
                    <td align="left"><?= $position["shares"] ?></td>
                    <td align="left"><?= $position["price"] ?></td>
                    <td align="left"><?= $position["total"] ?></td>
                </tr>
                
			<?php endforeach ?>
		
	</table>
    </div>
    </br>
    
<div>
    <a href="history.php">Trade history</a>
</div>
<div>
    <a href="quote.php">Get Stock Quote</a>
</div>
<div>
    <a href="buy.php">Buy Stocks</a>
</div>
<div>
    <a href="sell.php">Sell Stocks</a>
</div>
<div>
    <a href="deposit.php">Make a deposit</a>
</div>
<div>
    <a href="logout.php">Log Out</a>
</div>

