function validateInput(event) {
    const input = event.target;
    if (input.value < 0) {
        alert("Timeout value cannot be negative. Please enter a valid positive number.");
        input.value = '';
    }
}

function showNotification(message, isSuccess) {
    const notification = document.getElementById('notification');
    notification.textContent = message;
    notification.className = 'notification ' + (isSuccess ? 'success' : 'error');
    notification.style.display = 'block';
}

function sendData(action) {
    const redTimeout = document.getElementById('red-timeout').value;
    const yellowTimeout = document.getElementById('yellow-timeout').value;
    const greenTimeout = document.getElementById('green-timeout').value;

    if (redTimeout && yellowTimeout && greenTimeout) {
        // Simulate sending data to the server
        const success = Math.random() > 0.2; // 80% chance of success
        if (success) {
            showNotification(`Data sent successfully for ${action} action!`, true);
        } else {
            showNotification(`Failed to send data for ${action} action. Please try again.`, false);
        }
    } else {
        showNotification('Please enter valid timeouts for all lights.', false);
    }
}

window.onload = function () {
    const timeoutInputs = document.querySelectorAll('input[type="number"]');
    timeoutInputs.forEach(input => {
        input.addEventListener('input', validateInput);
    });

    document.getElementById('start-button').addEventListener('click', function () {
        sendData('start');
    });

    document.getElementById('stop-button').addEventListener('click', function () {
        sendData('stop');
    });
};
