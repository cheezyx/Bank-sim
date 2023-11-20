DELIMITER //

CREATE PROCEDURE TransferBalance(
    IN p_from_account_id INT,
    IN p_to_account_id INT,
    IN p_amount DECIMAL(10, 2),
    IN p_description VARCHAR(255),
    IN p_transaction_type INT,
    OUT p_message TEXT
)
BEGIN
    -- Declare local variables to hold account balances
    DECLARE v_from_balance DECIMAL(10, 2);
    DECLARE v_to_balance DECIMAL(10, 2);

    -- Start a transaction
    START TRANSACTION;

    -- Check the balance of the from account
    SELECT balance INTO v_from_balance FROM accounts WHERE account_id = p_from_account_id FOR UPDATE;

    -- Verify if sufficient funds are available
    IF v_from_balance < p_amount THEN
        SET p_message = 'Insufficient funds';
        ROLLBACK;
    ELSE
        -- Deduct the amount from the from account
        UPDATE accounts SET balance = balance - p_amount WHERE account_id = p_from_account_id;

        -- Add the amount to the to account
        UPDATE accounts SET balance = balance + p_amount WHERE account_id = p_to_account_id;

        -- Log the transaction
        INSERT INTO transactions (from_account_id, to_account_id, amount, date_time, description, transaction_type)
        VALUES (p_from_account_id, p_to_account_id, p_amount, NOW(), p_description, p_transaction_type);

        SET p_message = 'Transfer successful';
        COMMIT;
    END IF;
END //

DELIMITER ;