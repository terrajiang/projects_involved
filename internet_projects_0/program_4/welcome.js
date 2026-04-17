const textbox = document.getElementsByTagName('input')[0];
const submit_btn = document.getElementsByTagName('input')[1];


window.onload = function() {
  textbox.value = get_username();
}


submit_btn.addEventListener('click', submit);

document.getElementById("txt").addEventListener("keyup", function(e) {
  e.preventDefault();
  if (e.keyCode === 13) {
    document.getElementById("sub").click();
  }
});


function submit() {
  const typed = textbox.value;

  let alert_msg = '';
  let invalid = false;
  let onlyLastOne = true;

  if (typed.length < 5 || typed.length > 40) {
    invalid = true;
    onlyLastOne = false;
    alert_msg += 'Username must be 5 characters or longer.\n';
  }

  for (const char in typed) {
    if (typed[char] === ' ') {
      invalid = true;

      if (alert_msg.includes('Username cannot contain spaces.\n')) {
        continue;
      } else {
        alert_msg += 'Username cannot contain spaces.\n';
      }
    }
    if (typed[char] === ',') {
      invalid = true;

      if (alert_msg.includes('Username cannot contain commas.\n')) {
        continue;
      } else {
        alert_msg += 'Username cannot contain commas.\n';
      }
    }
    if (typed[char] === ';') {
      invalid = true;

      if (alert_msg.includes('Username cannot contain semicolons.\n')) {
        continue;
      } else {
        alert_msg += 'Username cannot contain semicolons.\n';
      }
    }
    if (typed[char] === '=') {
      invalid = true;

      if (alert_msg.includes('Username cannot contain =.\n')) {
        continue;
      } else {
        alert_msg += 'Username cannot contain =.\n';
      }
    }
    if (typed[char] === '&') {
      invalid = true;

      if (alert_msg.includes('Username cannot contain &.\n')) {
        continue;
      } else {
        alert_msg += 'Username cannot contain &.\n';
      }
    }
  }

  for (const char in typed) {
    const list = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^*()-_+[]{}:'|`~<.>/?";

    if (!list.includes(typed[char])) {
      invalid = true;
    }
  }


  if (invalid && onlyLastOne) {
    alert("Username can only use characters from the following string: \nabcdefghijklmnopqrstuvwxyz\nABCDEFGHIJKLMNOPQRSTUVWXYZ\n0123456789\n!@#$%^*()-_+[]{}:'|`~<.>/?");
  } else if (invalid) {
    alert(alert_msg);
  } else {
    document.cookie = `username=${typed}; expires=${an_hr_future()}}`;
		window.location.href = "shut_the_box.html";
  }
}


function an_hr_future() {
  let anHrLater = new Date();
  anHrLater.setHours(anHrLater.getHours() + 1);
  return anHrLater.toUTCString();
}