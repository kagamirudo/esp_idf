function validateInput(event) {
    const input = event.target;
    if (input.value < 0) {
        alert("Timeout value cannot be negative. Please enter a valid positive number.");
        input.value = '';
    }
}

function showNotification(message, isSuccess) {
    const notification = document.getElementById('notification');
    if (message.includes('timeouts:')) {
        const [firstPart, secondPart] = message.split('timeouts:');
        notification.innerHTML = `${firstPart}timeouts:<br>${secondPart.trim()}`;
    } else {
        notification.textContent = message;
    }
    notification.className = 'notification ' + (isSuccess ? 'success' : 'error');
    notification.style.display = 'block';
}

function sendData(action) {
    const form = document.getElementById('traffic-light-form');
    const formData = new FormData(form);
    const searchParams = new URLSearchParams(formData);

    if (action === 'stop') {
        searchParams.set('stop-button', '1');
    }

    fetch('/get?' + searchParams.toString(), {
        method: 'GET',
    })
        .then(response => response.text())
        .then(data => {
            showNotification(data, true);
        })
        .catch((error) => {
            console.error('Error:', error);
            showNotification('An error occurred. Please try again.', false);
        });
}

window.onload = function () {
    const timeoutInputs = document.querySelectorAll('input[type="number"]');
    timeoutInputs.forEach(input => {
        input.addEventListener('input', validateInput);
    });

    document.getElementById('traffic-light-form').addEventListener('submit', function (e) {
        e.preventDefault();
        sendData('start');
    });

    document.getElementById('stop-button').addEventListener('click', function () {
        sendData('stop');
    });
};
