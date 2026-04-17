const paragraph = document.getElementsByTagName('p')[1];

const again_btn = document.getElementsByTagName('input')[0];
const update_btn = document.getElementsByTagName('input')[1];
const stop_btn = document.getElementsByTagName('input')[2];

again_btn.addEventListener('click', function(){
  window.location.href = 'welcome.php';
});
update_btn.addEventListener('click', force_updating);
stop_btn.addEventListener('click', stop_updating);



let timeoutId = null;
print();


function print(){
  timeoutId = setTimeout(print, 8000);

  const request = new XMLHttpRequest();
  
  request.onload = function(){
    if (this.status === 200){
      paragraph.innerHTML = this.responseText.split('\n').join('<br>');
    }
  };
  
  request.open('GET', 'scores.txt' + '?v=' + Math.random());
  request.send();
}


function stop_updating(){
  clearTimeout(timeoutId);
}


function force_updating(){
  stop_updating();
  print();
}