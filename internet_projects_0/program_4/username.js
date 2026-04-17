function get_username() {
  let cookie = document.cookie;

  const name_values = cookie.split('; ');

  let foundUsername = false;
  for (const name_value of name_values) {
    if (name_value.startsWith('username=')) {
      foundUsername = true;
      return name_value.substring('username='.length);
    }
  }
  if (!foundUsername) {
    return '';
  }
}
