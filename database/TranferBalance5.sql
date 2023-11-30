DELIMITER //

CREATE PROCEDURE TransferBalance(
    IN p_from_account_id INT,
    IN p_to_account_id INT,
    IN p_amount DECIMAL(10, 2),
    IN p_description VARCHAR(255),
    OUT p_message TEXT
)
BEGIN
    DECLARE v_from_balance DECIMAL(10, 2);
    DECLARE v_to_balance DECIMAL(10, 2);

    START TRANSACTION;

    SELECT balance INTO v_from_balance FROM accounts WHERE account_id = p_from_account_id FOR UPDATE;

    IF v_from_balance < p_amount THEN
        SET p_message = 'Insufficient funds';
        ROLLBACK;
    ELSE
        UPDATE accounts SET balance = balance - p_amount WHERE account_id = p_from_account_id;
        UPDATE accounts SET balance = balance + p_amount WHERE account_id = p_to_account_id;

        INSERT INTO transactions (from_account_id, to_account_id, amount, date_time, description, transaction_type)
        VALUES (p_from_account_id, p_to_account_id, p_amount, NOW(), p_description, 'transfer');

        SET p_message = 'Transfer successful';
        COMMIT;
    END IF;
END //

DELIMITER ;

--  DROP PROCEDURE TransferBalance