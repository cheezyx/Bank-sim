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
    DECLARE v_from_account_type ENUM('debit', 'credit');
    DECLARE v_from_credit_limit DECIMAL(10, 2);

    START TRANSACTION;

    -- Hae tilin saldo, tyyppi ja luottoraja
    SELECT balance, account_type, credit_limit INTO v_from_balance, v_from_account_type, v_from_credit_limit
    FROM accounts WHERE account_id = p_from_account_id FOR UPDATE;

    -- Tarkista tilin tyyppi ja varojen riittävyys
    IF v_from_account_type = 'credit' THEN
        -- Credit-tilin tarkistus
        IF v_from_balance - p_amount < -v_from_credit_limit THEN
            SET p_message = 'Luottoraja ylitetty';
            ROLLBACK;
        ELSE
            -- Päivitä saldot ja kirjaa siirto
            UPDATE accounts SET balance = balance - p_amount WHERE account_id = p_from_account_id;
            UPDATE accounts SET balance = balance + p_amount WHERE account_id = p_to_account_id;
            INSERT INTO transactions (from_account_id, to_account_id, amount, date_time, description, transaction_type)
            VALUES (p_from_account_id, p_to_account_id, p_amount, NOW(), p_description, 'transfer');
            SET p_message = 'Siirto onnistui';
            COMMIT;
        END IF;
    ELSEIF v_from_account_type = 'debit' THEN
        -- Debit-tilin tarkistus
        IF v_from_balance - p_amount < 0 THEN
            SET p_message = 'Tilillä ei katetta';
            ROLLBACK;
        ELSE
            -- Päivitä saldot ja kirjaa siirto
            UPDATE accounts SET balance = balance - p_amount WHERE account_id = p_from_account_id;
            UPDATE accounts SET balance = balance + p_amount WHERE account_id = p_to_account_id;
            INSERT INTO transactions (from_account_id, to_account_id, amount, date_time, description, transaction_type)
            VALUES (p_from_account_id, p_to_account_id, p_amount, NOW(), p_description, 'transfer');
            SET p_message = 'Siirto onnistui';
            COMMIT;
        END IF;
    END IF;
END //

--  DROP PROCEDURE TransferBalance