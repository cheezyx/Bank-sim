DELIMITER //

CREATE PROCEDURE WithdrawBalance(
    IN p_account_id INT,
    IN p_amount DECIMAL(10, 2),
    OUT p_message TEXT
)
BEGIN
    DECLARE v_balance DECIMAL(10, 2);
    DECLARE v_account_type ENUM('debit', 'credit');
    DECLARE v_credit_limit DECIMAL(10, 2);

    -- Aloita transaktio
    START TRANSACTION;
    
    -- Tarkista, että summa on jaollinen luvulla 10
    IF p_amount % 10 != 0 THEN
        SET p_message = 'Summan tulee olla jaollinen luvulla 10';
        ROLLBACK;
    ELSE
        -- Hae tilin saldo, tyyppi ja luottoraja
        SELECT balance, account_type, credit_limit INTO v_balance, v_account_type, v_credit_limit
        FROM accounts WHERE account_id = p_account_id FOR UPDATE;
        
        -- Tarkista onko tilillä tarpeeksi varoja tai onko se luottotili
        IF v_account_type = 'credit' AND v_balance - p_amount < -v_credit_limit THEN
            SET p_message = 'Luottoraja ylitetty';
            ROLLBACK;
        ELSEIF v_account_type = 'debit' AND v_balance < p_amount THEN
            SET p_message = 'Tilillä ei katetta';
            ROLLBACK;
        ELSE
            -- Vähennä summa tililtä
            UPDATE accounts SET balance = balance - p_amount WHERE account_id = p_account_id;

            -- Kirjaa transaktio
            INSERT INTO transactions (from_account_id, to_account_id, amount, date_time, description, transaction_type)
            VALUES (p_account_id, NULL, p_amount, NOW(), 'Nosto', 'withdraw'); 

            SET p_message = 'Nosto onnistui';
            COMMIT;
        END IF;
    END IF;
END //

DELIMITER ;

 -- DROP PROCEDURE WithdrawBalance