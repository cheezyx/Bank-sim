CREATE DEFINER=`root`@`localhost` PROCEDURE `WithdrawBalance`(
    IN p_account_id INT,
    IN p_amount DECIMAL(10, 2),
    IN p_description VARCHAR(255),
    OUT p_message TEXT
)
BEGIN
    DECLARE v_balance DECIMAL(10, 2);

    SELECT balance INTO v_balance FROM accounts WHERE account_id = p_account_id;

    IF v_balance < p_amount THEN
        SET p_message = 'Tililla ei katetta';
    ELSE
        UPDATE accounts SET balance = balance - p_amount WHERE account_id = p_account_id;

        INSERT INTO transactions (from_account_id, to_account_id, amount, date_time, description, transaction_type)
        VALUES (p_account_id, NULL, p_amount, NOW(), p_description, 6); -- Assuming 6 represents a withdrawal

        SET p_message = 'Nosto onnistui';
    END IF;
END