
DELIMITER //

CREATE PROCEDURE WithdrawBalance(
    IN p_account_id INT,
    IN p_amount DECIMAL(10, 2),
    IN p_description VARCHAR(255),
    OUT p_message TEXT
)
BEGIN
    -- Declare local variables to hold account balances
	DECLARE v_balance DECIMAL(10, 2);
    
	-- Start a transaction
    START TRANSACTION;
    
	-- Check the balance of the from account
    SELECT balance INTO v_balance FROM accounts WHERE account_id = p_account_id FOR UPDATE;
    
	-- Verify if sufficient funds are available
    IF v_balance < p_amount THEN
        SET p_message = 'Insufficient funds';
        ROLLBACK;
        
     ELSE
	-- Deduct the amount from the from account
    UPDATE accounts SET balance = balance - p_amount WHERE account_id = p_account_id;

	-- Log the transaction
    INSERT INTO transactions (from_account_id, to_account_id, amount, date_time, description, transaction_type)
    VALUES (p_account_id, NULL, p_amount, NOW(), p_description, 'withdraw'); 

    SET p_message = 'Withdrawal successful';
        COMMIT;
    END IF;
END //

DELIMITER ;


 -- DROP PROCEDURE WithdrawBalance