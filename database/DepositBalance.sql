DELIMITER //

CREATE PROCEDURE DepositBalance(
    IN p_account_id INT,
    IN p_amount DECIMAL(10, 2),
    OUT p_message TEXT
)
BEGIN
    -- Aloita transaktio
    START TRANSACTION;

    -- Päivitä tili
    UPDATE accounts SET balance = balance + p_amount WHERE account_id = p_account_id;

    -- Kirjaa transaktio
    INSERT INTO transactions (from_account_id, to_account_id, amount, date_time, description, transaction_type)
    VALUES (NULL, p_account_id, p_amount, NOW(), 'Talletus', 'deposit'); 

    -- Jos kaikki meni hyvin, vahvista transaktio
    SET p_message = 'Talletus onnistui';
    COMMIT;
END //

DELIMITER ;

--  DROP PROCEDURE DepositBalance