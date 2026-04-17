let unchecked_total = 45;
let dice_roll = 0;

const dice_result = document.getElementsByTagName('span')[0];

const roll_dice_btn = document.getElementsByTagName('input')[0];
const submit_btn = document.getElementsByTagName('input')[10];
const finish_btn = document.getElementsByTagName('input')[11];

const boxes = document.getElementsByTagName('td');
const checkboxes = document.getElementsByTagName('input');


roll_dice_btn.addEventListener('click', roll_dice);

for (let i = 0; i < 9; ++i) {
  boxes[i].addEventListener('click', function() {
    checkboxes[i + 1].checked = !checkboxes[i + 1].checked;
  });
}

submit_btn.addEventListener('click', submit);
finish_btn.addEventListener('click', finish);



function roll_dice() {
  let i = Math.floor(1 + 6 * Math.random());
  let j = Math.floor(1 + 6 * Math.random());
  dice_roll = i + j;

  dice_result.innerHTML = `${i} + ${j} = ${dice_roll}`;

  roll_dice_btn.disabled = !roll_dice_btn.disabled;
  submit_btn.disabled = !submit_btn.disabled;
}


window.onload = function() {
  roll_dice_btn.disabled = false;
  submit_btn.disabled = true;
}


function roll_die() {
  dice_roll = Math.floor(1 + 6 * Math.random());

  dice_result.innerHTML = `${dice_roll}`;

  roll_dice_btn.disabled = !roll_dice_btn.disabled;
  submit_btn.disabled = !submit_btn.disabled;
}


function sum_checked_values() {
  unchecked_total = 45;
  for (let i = 1; i < 10; ++i) {
    if (checkboxes[i].disabled || checkboxes[i].checked) {
      unchecked_total -= i;
    }
  }
  return 45 - unchecked_total;
}


function submit() {
  let checkedSum = 0;
  for (let i = 1; i < 10; ++i) {
    if (checkboxes[i].checked && checkboxes[i].disabled) {
      checkboxes[i].checked = false;
    }

    if (checkboxes[i].checked) {
      checkedSum += i;
    }
  }

  if (checkedSum !== dice_roll) {
    alert('The total of the boxes you selected does not match the dice roll. \n Please make another selection and try again.');
  } else {
    submit_btn.disabled = !submit_btn.disabled;
    roll_dice_btn.disabled = !roll_dice_btn.disabled;
    
    for (let i = 1; i < 10; ++i) {
    	if (checkboxes[i].checked) {
				checkboxes[i].checked = false;
        checkboxes[i].disabled = true;
      }
    }

    if ((45 - sum_checked_values()) <= 6) {
      roll_dice_btn.removeEventListener('click', roll_dice);
      roll_dice_btn.addEventListener('click', roll_die);
    }

    dice_result.innerHTML = '';
  }
}


function finish() {
  finish_btn.disabled = true;

  sum_checked_values();
  alert(`Your score is ${unchecked_total}`);

  const request = new XMLHttpRequest();

  let username = get_username();

  request.open('POST', 'score.php');
  request.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');
  request.send(`username=${username}&score=${unchecked_total}`);

  window.location.href = 'scores.php';
}
