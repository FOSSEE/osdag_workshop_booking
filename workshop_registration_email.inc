<?php
/**
 * Implementation of hook_mail().
 */
function osdag_workshop_booking_mail($key, &$message, $params)
{
    global $user;
    $language = $message['language'];
    switch ($key)
    {
        case 'proposal_received':
        /* mail template */
            break;
        case 'proposal_approved':
        /* mail template */
            break;
        case 'proposal_disapproved':
        /* mail template */
            break;
    }
}
