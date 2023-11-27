import React from 'react';
import { useNavigate } from 'react-router-dom';

function CardTypeSelection() {
  const navigate = useNavigate();

  const handleSelection = (type) => {
    // Tallenna valittu korttityyppi, esimerkiksi local storageen
    localStorage.setItem('selected_card_type', type);
    // Ohjaa käyttäjä AutomatPage-sivulle
    navigate('/automat');
  };

  return (
    <div>
      <h1>Valitse tilimuoto</h1>
      <button onClick={() => handleSelection('credit')}>Credit</button>
      <button onClick={() => handleSelection('debit')}>Debit</button>
    </div>
  );
}

export default CardTypeSelection;