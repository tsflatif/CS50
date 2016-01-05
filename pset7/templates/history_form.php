</div>
	</br>
    <table id="overview" style="width:100%">
        <tr>
            <th>Transaction</th>
            <th>Date/Time</th>
            <th>Symbol</th>
            <th>Shares</th>
            <th>Price</th>
        </tr>
                
						  
			<?php foreach ($history as $position): ?>

				<tr>
                    <td align="left"><?= $position["status"] ?></td>
                    <td align="left"><?= $position["date"] ?></td>
                    <td align="left"><?= $position["symbol"] ?></td>
                    <td align="left"><?= $position["shares"] ?></td>
                    <td align="left"><?= $position["price"] ?></td>
                </tr>
                
			<?php endforeach ?>
		
	</table>
	
	<div>
    <a href="index.php">Back to main</a>
</div>
</div>


