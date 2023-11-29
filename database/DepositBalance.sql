DELIMITER //

CREATE PROCEDURE DepositBalance(
    IN p_account_id INT,
    IN p_amount DECIMAL(10, 2),
    IN p_description VARCHAR(255),
    OUT p_message TEXT
)
BEGIN

    UPDATE accounts SET balance = balance + p_amount WHERE account_id = p_account_id;


    INSERT INTO transactions (from_account_id, to_account_id, amount, date_time, description, transaction_type)
    VALUES (NULL, p_account_id, p_amount, NOW(), p_description, 'deposit'); 

    SET p_message = 'Talletus onnistui';
END //

DELIMITER ;

--  DROP PROCEDURE DepositBalance