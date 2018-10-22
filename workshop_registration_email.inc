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
			/* initializing data */
			$proposal_q = db_query("SELECT * FROM {osdag_workshop_booking_proposal} WHERE id = %d LIMIT 1", $params['proposal_received']['proposal_id']);
			$proposal_data = db_fetch_object($proposal_q);
			$user_data = user_load($params['proposal_received']['user_id']);
			$message['headers'] = $params['proposal_received']['headers'];
			$message['subject'] = t('[!site_name][Workshop Booking] Your request for osdag workshop has been received', array(
				'!site_name' => variable_get('site_name', '')
			), array(
				'language' => $language->language
			));
			$message['body'] = array(
				'body' => t('
Dear !user_name,

We have received your request for osdag workshop.


Your request is under review and you will soon receive an email from us regarding the same.

Best Wishes,

Osdag Team,
FOSSEE, IIT Bombay', array(
					'!site_name' => variable_get('site_name', ''),
					'!user_name' => $user_data->name
				), array(
					'language' => $language->language
				))
			);
            break;
        case 'proposal_approved':
			/* initializing data */
			$proposal_q = db_query("SELECT * FROM {osdag_workshop_booking_proposal} WHERE id = %d LIMIT 1", $params['proposal_approved']['proposal_id']);
			$proposal_data = db_fetch_object($proposal_q);
			$user_data = user_load($params['proposal_approved']['user_id']);
			$message['headers'] = $params['proposal_approved']['headers'];
			$message['subject'] = t('[!site_name][Workshop Booking] Your request for osdag workshop has been approved', array(
				'!site_name' => variable_get('site_name', '')
			), array(
				'language' => $language->language
			));
			$message['body'] = array(
				'body' => t('
Dear !user_name,

Your request for osdag workshop has been approved.


Our team will contact you on email regarding the same.

Best Wishes,

Osdag Team,
FOSSEE, IIT Bombay', array(
					'!site_name' => variable_get('site_name', ''),
					'!user_name' => $user_data->name
				), array(
					'language' => $language->language
				))
			);
            break;
        case 'proposal_disapproved':
			/* initializing data */
			$proposal_q = db_query("SELECT * FROM {osdag_workshop_booking_proposal} WHERE id = %d LIMIT 1", $params['proposal_disapproved']['proposal_id']);
			$proposal_data = db_fetch_object($proposal_q);
			$user_data = user_load($params['proposal_disapproved']['user_id']);
			$message['headers'] = $params['proposal_disapproved']['headers'];
			$message['subject'] = t('[!site_name][Workshop Booking] Your request for osdag workshop has been disapproved', array(
				'!site_name' => variable_get('site_name', '')
			), array(
				'language' => $language->language
			));
			$message['body'] = array(
				'body' => t('
Dear !user_name,

We have received your request for osdag workshop.


Your request is under review and you will soon receive an email from us regarding the same.

Best Wishes,

Osdag Team,
FOSSEE, IIT Bombay', array(
					'!site_name' => variable_get('site_name', ''),
					'!user_name' => $user_data->name
				), array(
					'language' => $language->language
				))
			);
            break;
    }
}
