<?php
// You can find all functions regarding manage proposal
/*
textbook companion proposal table column "proposal_status" field values means
0 = 'Pending';
1 = 'Approved';
2 = 'Dis-approved';
3 = 'Completed';
4 = 'External';
5 = 'Unknown';
*/
function _proposal_pending()
{
    /* get pending proposals to be approved */
    $pending_rows = array();
    $pending_q = db_query("SELECT * FROM {osdag_workshop_booking_proposal}
                    WHERE proposal_status = 0 ORDER BY id DESC");
    $i=1;
    while ($pending_data = $pending_q->fetchObject())
    {
        $pending_rows[$pending_data->id] = array(
            $i,
            date('d-m-Y', $pending_data->creation_date),
            l($pending_data->fname.' ' . $pending_data->lname, 'user/' .
            $pending_data->uid),
            $pending_data->workshop_type,
            $pending_data->from_w_date.' to '. $pending_data->end_w_date,
            l('Approve', 'osdag-workshop-booking/manage-proposal/approve/' .
            $pending_data->id) //. ' | ' .
            /*l('Edit', 'osdag-workshop-booking/manage-proposal/edit/' .
            $pending_data->id)*/
        );
        $i++;
    } //$pending_data = $pending_q->fetchObject()
    /* check if there are any pending proposals */
    if (!$pending_rows)
    {
        drupal_set_message(t('There are no pending proposals.'), 'status');
        return '';
    } //!$pending_rows
    $pending_header = array(
        'Sr. No.',
        'Date',
        'Coordinater Name',
        'Workshop Type',
        'Proposed Workshop date',
        'Action'
    );
    $output = theme('table', array(
        'header' => $pending_header,
        'rows' => $pending_rows
    ));
    return $output;
}
/* view all proposals */
function _proposal_all()
{
    /* get pending proposals to be approved */
    $proposal_rows = array();
    $proposal_q = db_query("SELECT * FROM {osdag_workshop_booking_proposal} 
                     ORDER BY id DESC");
    $i=1;
    while ($proposal_data = $proposal_q->fetchObject())
    {
        $proposal_status = '';
        $action = '';
        switch ($proposal_data->proposal_status)
        {
            case 0:
                $proposal_status = 'Pending';
                $action = l('Approve', 'osdag-workshop-booking/manage-proposal/approve/' .
            $proposal_data->id);
                break;
            case 1:
                $proposal_status = 'Approved';
                break;
            case 2:
                $proposal_status = 'Dis-approved';
                break;
            case 3:
                $proposal_status = 'Completed';
                break;
            case 4:
                $proposal_status = 'External';
                break;
            default:
                $proposal_status = 'Unknown';
                break;
        } //$proposal_data->proposal_status
        $proposal_rows[$proposal_data->id] = array(
            $i,
            date('d-m-Y', $proposal_data->creation_date),
            l($proposal_data->fname.' ' . $proposal_data->lname, 'user/' .
            $proposal_data->uid),
            $proposal_data->workshop_type,
            $proposal_data->from_w_date.' to '. $proposal_data->end_w_date,
            $proposal_status,
            $action,
        );
        $i++;
    } //$pending_data = $pending_q->fetchObject()
    /* check if there are any pending proposals */
    if (!$proposal_rows)
    {
        drupal_set_message(t('There are no pending proposals.'), 'status');
        return '';
    } //!$pending_rows
    $proposal_header = array(
        'Sr. No.',
        'Date',
        'Coordinater Name',
        'Workshop Type',
        'Proposed Workshop date',
        'Status',
        'Action'
    );
    $output = theme('table', array(
        'header' => $proposal_header,
        'rows' => $proposal_rows
    ));
    return $output;
}
/* Proposal approval form */
function osdag_workshop_booking_proposal_approval_form($form, &$form_state)
{
    global $user;
    /* get current proposal */
    $proposal_id = arg(3);
    $result = db_query("SELECT * FROM {osdag_workshop_booking_proposal} 
                WHERE proposal_status = 0 and id = :id", 
                array(':id' =>$proposal_id));
    if ($result)
    {
        if ($row = $result->fetchObject())
        {
            /* everything ok */
        } //$row = $result->fetchObject()
        else
        {
            drupal_set_message(t('Invalid proposal selected. Please try again.
            '), 'error');
            drupal_goto('manage-proposal');
            return;
        }
    } //$result
    else
    {
        drupal_set_message(t('Invalid proposal selected. Please try again.'), 
        'error');
        drupal_goto('manage-proposal');
        return;
    }
    
        $form['#attributes'] = array(
        'enctype' => "multipart/form-data"
    );
    $form['personal_info'] = array(
        '#type' => 'fieldset',
        '#title' => t('Personal Information'),
        '#tree' => TRUE,
    );
    $full_name = $row->title .' '. $row->fname. ' '. $row->lname;
    $form['personal_info']['full_name'] = array(
        '#type' => 'item',
        '#title' => t('Full Name'),
        '#markup' => $full_name,
    );
    $form['personal_info']['designation'] = array(
        '#type' => 'item',
        '#title' => t('Designation'),
        '#markup' => $row->designation,
    );
    $form['personal_info']['email_id'] = array(
        '#type' => 'item',
        '#title' => t('Email'),
        '#markup' => $row->email_id,
    );
    $form['personal_info']['contact_no'] = array(
        '#type' => 'item',
        '#title' => t('Contact No.'),
        '#markup' => $row->contact_no,
    );
    $form['organization_info'] = array(
        '#type' => 'fieldset',
        '#title' => t('Organization Information'),
        '#tree' => TRUE,
    );
    $form['organization_info']['institute_company'] = array(
        '#type' => 'item',
        '#title' => t('Name of the Institute/Company'),
        '#markup' => $row->institute_company,
    );
    $form['organization_info']['alt_email_id'] = array(
        '#type' => 'item',
        '#title' => t('Official (Institute/Company) Email address'),
        '#markup' => $row->address_of_institute_company,
    );
    $form['organization_info']['institute_company_address'] = array(
        '#type' => 'item',
        '#title' => t('Address of the Institute/Company'),
        '#markup' => $row->org_email,
    );
    $form['organization_info']['city_district'] = array(
        '#type' => 'item',
        '#title' => t('City/District'),
        '#markup' => $row->city_district,
    );
    $form['organization_info']['all_state'] = array(
        '#type' => 'item',
        '#title' => t('State'),
        '#markup' => $row->indian_state,
    );
    $form['organization_info']['pincode'] = array(
        '#type' => 'item',
        '#title' => t('Pincode'),
        '#markup' => $row->pincode,
    );
    $form['workshop_info'] = array(
        '#type' => 'fieldset',
        '#title' => t('Workshop Information'),
        '#tree' => TRUE,
    );
    $form['workshop_info']['workshop_type'] = array(
        '#type' => 'item',
        '#title' => t('Workshop type'),
        '#markup' => $row->workshop_type,
    );
    $form['workshop_info']['expected_number_of_participants'] = array(
        '#type' => 'item',
        '#title' => t('Expected number of participants'),
        '#markup' => $row->exp_number_of_participent,
    );
    $form['workshop_info']['participant_type'] = array(
        '#type' => 'item',
        '#title' => t('Participant type'),
        '#markup' => $row->participant_type,
    );
    $form['workshop_info']['checklist_group'] = array(
        '#type' => 'fieldset',
        '#title' => t('Workshop Checklist'),
        '#tree' => TRUE,
    );
    $form['workshop_info']['checklist_group']['is_computer_lab_available'] = 
    array(
        '#type' => 'item',
        '#title' => t('Is a computer lab available at the organizing 
        institute/company?'),
        '#markup' => $row->available_computer,
    );
    if($row->available_computer == 'Yes'){
    $form['workshop_info']['checklist_group']['if_yes_1'] = array(
        '#type' => 'item',
        '#title' => t('What is the Operating system (Windows, Linux etc.) 
        [mention OS with configuration. Ex. Windows 10 or Ubuntu 18.04 etc]'),
        '#markup' => $row->if_yes_1,
    );
    $form['workshop_info']['checklist_group']['if_yes_2'] = array(
        '#type' => 'item',
        '#title' => t('Is there a projection facility at the computer lab?'),
        '#markup' => $row->if_yes_2,
    );
    $form['workshop_info']['checklist_group']['if_yes_3'] = array(
        '#type' => 'item',
        '#title' => t('Are all the computers connected to the Internet?'),
        '#markup' => $row->if_yes_3,
    );
    }else{
    $form['workshop_info']['checklist_group']['if_no_1'] = array(
        '#type' => 'item',
        '#title' => t('Every participant has to have an individual computer with
        Osdag pre-installed in it.'),
        '#markup' => $row->if_no_1,
    );
    $form['workshop_info']['checklist_group']['if_no_2'] = array(
        '#type' => 'item',
        '#title' => t('All the participants should be accommodated in a single
        room with audio-visual projection facilities.'),
        '#markup' => $row->if_no_2,
    );
    }
    $form['workshop_info']['volunteers'] = array(
        '#type' => 'item',
        '#title' => t('Volunteers'),
        '#markup' => $row->volunteers,
    );
    $form['workshop_info']['checklist_group']['suggested_date'] = array(
        '#type' => 'fieldset',
        '#title' => t('Suggested Date(s)'),
        '#tree' => TRUE,
    );
    $form['workshop_info']['checklist_group']['suggested_date']['start_date'] =
    array(
        '#type' => 'item',
        '#markup' => $row->from_w_date .' to '. $row->end_w_date,
    );
    $form['workshop_info']['proposed_travel_arrangement'] = array(
        '#type' => 'item',
        '#title' => t('What is the proposed travel arrangement for the Osdag 
        resource people'),
        '#markup' => $row->travel_arrangement,
    );
    $form['workshop_info']['how_did_you_here'] = array(
        '#type' => 'item',
        '#title' => t('How did you hear about Osdag training workshop?'),
        '#markup' => $row->how_did_you_here,
    );

    $form['approve_disapprove'] = array(
        '#type' => 'radios',
        '#title' => t('Approve/ Disapprove request'),
        '#options' => array('approve' => 'Approve', 'disapprove' => 
        'Disapprove'),
    );
    $form['message'] = array(
        '#type' => 'textarea',
        '#title' => t('Reason for disapproval'),
        '#states' => array(
            'visible' => array(
                ':input[name="approve_disapprove"]' => array(
                    'value' => 'disapprove'
                )
            ),
            'required' => array(
                ':input[name="approve_disapprove"]' => array(
                    'value' => 'disapprove'
                )
            )
        )
    );
    $form['proposal_id'] = array(
        '#type' => 'hidden',
        '#value' => $proposal_id
    );
    $form['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Submit')
    );
    $form['cancel'] = array(
        '#type' => 'item',
        '#markup' => "<input type='button' class='button-user' value='Back' onclick='window.history.go(-1); return false;'/>",
    );
    return $form;
}
function osdag_workshop_booking_proposal_approval_form_submit($form, &$form_state)
{
    global $user;
        /* get current proposal */
    $proposal_id = $form_state['values']['proposal_id'];
    $result = db_query("SELECT * FROM {osdag_workshop_booking_proposal} WHERE
    proposal_status = 0 and id = :proposal_id", array(
        ':proposal_id' => $proposal_id
    ));
    if ($result)
    {
        if ($row = $result->fetchObject())
        {
            /* everything ok */
        } //$row = $result->fetchObject()
        else
        {
            drupal_set_message(t('Invalid proposal selected. Please try again.'
            ), 'error');
            drupal_goto('osdag-workshop-booking/manage-proposal');
            return;
        }
    } //$result
    else
    {
        drupal_set_message(t('Invalid proposal selected. Please try again.'),
        'error');
        drupal_goto('osdag-workshop-booking/manage-proposal');
        return;
    }
    /* disapprove */
    if ($form_state['values']['approve_disapprove'] == 'disapprove')
    {
        db_query("UPDATE {osdag_workshop_booking_proposal} SET approver_uid =
        :approver_uid, approval_date = :approval_date, proposal_status = 2,
        disapprove_message = :message WHERE id = :id", array(
            ':approver_uid' => $user->uid,
            ':approval_date' => time(),
            ':message' => $form_state['values']['message'],
            ':id' => $proposal_id
        ));
        /* sending email */
        $osdag_user = user_load($row->uid);
        $email_to = $osdag_user->mail;
        $from = variable_get('osdag_workshop_booking_from_email', '');
        $bcc = variable_get('osdag_workshop_booking_bcc_emails', '');
        $cc = variable_get('osdag_workshop_booking_cc_emails', '');
        $params['proposal_disapproved']['proposal_id'] = $proposal_id;
        $params['proposal_disapproved']['user_id'] = $row->uid;
        $params['proposal_disapproved']['headers'] = array(
            'From' => $from,
            'MIME-Version' => '1.0',
            'Content-Type' => 'text/plain; charset=UTF-8; format=flowed; 
            delsp=yes',
            'Content-Transfer-Encoding' => '8Bit',
            'X-Mailer' => 'Drupal',
            'Cc' => $cc,
            'Bcc' => $bcc
        );
       // if (!drupal_mail('osdag_workshop_booking', 'proposal_disapproved', $email_to, language_default(), $params, $from, TRUE))
       //     drupal_set_message('Error sending email message.', 'error');
        drupal_set_message('Proposal dis-approved. User has been notified of
        the dis-approval.', 'error');
        drupal_goto('osdag-workshop-booking/manage-proposal');
        return;
    }elseif($form_state['values']['approve_disapprove'] == 'approve'){
        db_query("UPDATE {osdag_workshop_booking_proposal} SET approver_uid =
        :approver_uid, approval_date = :approval_date,
        proposal_status = 1, disapprove_message = :message WHERE id = :id",
        array(
            ':approver_uid' => $user->uid,
            ':approval_date' => time(),
            ':message' => 'none',
            ':id' => $proposal_id
        ));
            /* sending email */
        $osdag_user = user_load($row->uid);
        $email_to = $osdag_user->mail;
        $from = variable_get('osdag_workshop_booking_from_email', '');
        $bcc = variable_get('osdag_workshop_booking_bcc_emails', '');
        $cc = variable_get('osdag_workshop_booking_cc_emails', '');
        $params['proposal_approved']['proposal_id'] = $proposal_id;
        $params['proposal_approved']['user_id'] = $row->uid;
        $params['proposal_approved']['headers'] = array(
            'From' => $from,
            'MIME-Version' => '1.0',
            'Content-Type' => 'text/plain; charset=UTF-8; format=flowed;
            delsp=yes',
            'Content-Transfer-Encoding' => '8Bit',
            'X-Mailer' => 'Drupal',
            'Cc' => $cc,
            'Bcc' => $bcc
        );
       // if (!drupal_mail('osdag_workshop_booking', 'proposal_approved', $email_to, language_default(), $params, $from, TRUE))
       //     drupal_set_message('Error sending email message.', 'error');
        drupal_set_message('Proposal approved. User has been notified of the
        approval', 'status');
        drupal_goto('osdag-workshop-booking/manage-proposal');
        return;
    }else{
        drupal_set_message('Something went wrong. Please contact to 
        administrator', 'error');
        return;
    }

}
