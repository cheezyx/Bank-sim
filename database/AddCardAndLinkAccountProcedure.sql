DELIMITER //

CREATE PROCEDURE AddCardAndLinkAccount(
    IN new_customer_id INT,
    IN new_card_type ENUM('debit', 'credit', 'dual'),
    IN new_pin_hashed VARCHAR(255),
    IN account1_id INT,
    IN account2_id INT
)
BEGIN
    DECLARE account1_exists INT;
    DECLARE account2_exists INT;
    DECLARE account1_type VARCHAR(10);
    DECLARE account2_type VARCHAR(10);
    DECLARE cardTypeMismatch BOOLEAN DEFAULT FALSE;

    -- Aloita transaktio
    START TRANSACTION;

    -- Tarkista, että annetut tilit ovat olemassa
    SELECT COUNT(*) INTO account1_exists FROM accounts WHERE account_id = account1_id;
    IF account2_id IS NOT NULL THEN
        SELECT COUNT(*) INTO account2_exists FROM accounts WHERE account_id = account2_id;
    ELSE
        SET account2_exists = 1; -- Aseta oletusarvo, jos account2_id:tä ei ole annettu
    END IF;

    IF (account1_exists = 0 OR account2_exists = 0) THEN
        SIGNAL SQLSTATE '45000'
        SET MESSAGE_TEXT = 'One or more accounts do not exist';
        ROLLBACK;
    ELSE
        -- Hae tilien tyypit
        SELECT account_type INTO account1_type FROM accounts WHERE account_id = account1_id;
        IF account2_id IS NOT NULL THEN
            SELECT account_type INTO account2_type FROM accounts WHERE account_id = account2_id;
        END IF;

        -- Tarkista kortin ja tilien yhteensopivuus
        IF new_card_type IN ('debit', 'credit') AND (account2_id IS NOT NULL OR account1_type != new_card_type) THEN
            SET cardTypeMismatch = TRUE;
        END IF;

        IF new_card_type = 'dual' AND (account1_type = account2_type) THEN
            SET cardTypeMismatch = TRUE;
        END IF;

        IF cardTypeMismatch THEN
            SIGNAL SQLSTATE '45000'
            SET MESSAGE_TEXT = 'Card type and account types mismatch or incorrect number of accounts';
            ROLLBACK;
        ELSE
            -- Lisää kortti
            INSERT INTO cards (customer_id, card_type, pin_hashed) VALUES (new_customer_id, new_card_type, new_pin_hashed);
            SET @new_card_id = LAST_INSERT_ID();

            -- Linkitä ensimmäinen tili korttiin
            INSERT INTO card_privileges (card_id, account_id) VALUES (@new_card_id, account1_id);

            -- Linkitä toinen tili korttiin, jos dual-kortti ja toinen tili määritelty
            IF new_card_type = 'dual' AND account2_id IS NOT NULL THEN
                INSERT INTO card_privileges (card_id, account_id) VALUES (@new_card_id, account2_id);
            END IF;

            -- Jos kaikki meni hyvin, vahvista transaktio
            COMMIT;
        END IF;
    END IF;
END //

DELIMITER ;

--  DROP PROCEDURE AddCardAndLinkAccount