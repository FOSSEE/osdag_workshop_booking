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
            $full_name = $proposal_data->title .' ' . $proposal_data->fname . ' ' . $proposal_data->lname;
            $workshop_type = $proposal_data->workshop_type;
            $institute_company = $proposal_data->institute_company;
            if($proposal_data->from_w_date == $proposal_data->end_w_date){
                $suggested_date = $proposal_data->from_w_date;
            }else{
                $suggested_date = $proposal_data->from_w_date. 'to '. $proposal_data->end_w_date;
            }
            $user_data = user_load($params['proposal_received']['user_id']);
            $message['headers'] = $params['proposal_received']['headers'];
            $message['subject'] = t('[!site_name][OSDAG Workshop] Workshop request received', array(
                '!site_name' => variable_get('site_name', '')
            ), array(
                'language' => $language->language
            ));
            $message['body'] = array(
                'body' => t('
Dear '. $full_name .',

Thank you for showing your interest to organize a '. $workshop_type .' on
 structural steel design and detailing using Open Steel Design and Graphics
 (Osdag) at '. $institute_company .'on '. $suggested_date .'

Your request has been received and is awaiting for approval by PI of Osdag.
You will get a confirmation email on approval/disapproval/re-scheduling of the
 training workshop within 15 days.

Please note: Unless you get a confirmation email for this workshop with the list
 of instructions, your workshop shall be on the waiting list.


Thank you!

Best Regards,
Team Osdag,
FOSSEE, IIT Bombay.
', array(
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
            $full_name = $proposal_data->title .' ' . $proposal_data->fname . ' ' . $proposal_data->lname;
            $workshop_type = $proposal_data->workshop_type;
            $institute_company = $proposal_data->institute_company;
            if($proposal_data->from_w_date == $proposal_data->end_w_date){
                $suggested_date = $proposal_data->from_w_date;
            }else{
                $suggested_date = $proposal_data->from_w_date. 'to '. $proposal_data->end_w_date;
            }
            $user_data = user_load($params['proposal_approved']['user_id']);
            $message['headers'] = $params['proposal_approved']['headers'];
            $message['subject'] = t('[!site_name][OSDAG Workshop] Workshop request approved', array(
                '!site_name' => variable_get('site_name', '')
            ), array(
                'language' => $language->language
            ));
            $message['body'] = array(
                'body' => t('
Dear '. $full_name .',

Your request for organizing the training workshop has been approved by PI of
 Osdag.

The details of the workshop are as follows:'.
$Workshop type .'
Date: '. $suggested_date .'
Resource person: One resource person for every 25 participants, with a minimum
 of 2.

You will receive an email from team Osdag with detailed Instructions soon.

Thank you!

Best Regards,
Team Osdag,
FOSSEE, IIT Bombay.
', array(
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
            $full_name = $proposal_data->title .' ' . $proposal_data->fname . ' ' . $proposal_data->lname;
            $workshop_type = $proposal_data->workshop_type;
            $institute_company = $proposal_data->institute_company;
            if($proposal_data->from_w_date == $proposal_data->end_w_date){
                $suggested_date = $proposal_data->from_w_date;
            }else{
                $suggested_date = $proposal_data->from_w_date. 'to '. $proposal_data->end_w_date;
            }
            $user_data = user_load($params['proposal_disapproved']['user_id']);
            $message['headers'] = $params['proposal_disapproved']['headers'];
            $message['subject'] = t('[!site_name][OSDAG Workshop] Workshop request disapproved', array(
                '!site_name' => variable_get('site_name', '')
            ), array(
                'language' => $language->language
            ));
            $message['body'] = array(
                'body' => t('
Dear '. $full_name .',


We regret to inform you that your request for organizing the training workshop
 has been disapproved by PI of Osdag due to [reason]


Thank you!

Best Regards,
Team Osdag,
FOSSEE, IIT Bombay.', array(
                    '!site_name' => variable_get('site_name', ''),
                    '!user_name' => $user_data->name
                ), array(
                    'language' => $language->language
                ))
            );
            break;
    }
}
