import React, { useState, useEffect } from 'react';
import { useNavigate } from 'react-router-dom';

const CardTypeSelection = () => {
  const navigate = useNavigate();
  const [accounts, setAccounts] = useState([]);

  useEffect(() => {
      // Lue tilitiedot local storagesta tai contextista
      const storedAccounts = JSON.parse(localStorage.getItem('accounts'));
      if (storedAccounts) {
          setAccounts(storedAccounts);
      }
  }, []);

  const handleSelection = (type) => {
      localStorage.setItem('selected_card_type', type);
      navigate('/automat');
  };

  return (
      <div>
          <h1>Valitse tilimuoto</h1>
          <button onClick={() => handleSelection('credit')}>Credit</button>
          <button onClick={() => handleSelection('debit')}>Debit</button>
      </div>
  );
};

export default CardTypeSelection;