<?php
// $Id$
/*
Approval Status :
0 - Pending
1 - Approved
2 - Dis-Approved
3 - Solved
Solution Status :
0 - Pending
1 - Approved
2 - Dis-Approved
Solution Display :
0 - No
1 - Yes

Tables :
lab_migration_solution : approval_status
0 - Pending
1 - Approved
2 - Disapproved (delete it)
*/
/* workshop booking registration form */
function osdag_workshop_booking_form($form, &$form_state)
{
    global $user;
    /************************ start approve book details ************************/
    $query = db_select('osdag_workshop_booking');
    $query->fields('osdag_workshop_booking');
    $query->condition('uid', $user->uid);
    $query->orderBy('id', 'DESC');
    $query->range(0, 1);
    $proposal_q = $query->execute();
    $proposal_data = $proposal_q->fetchObject();
    if ($proposal_data)
    {
        if ($proposal_data->approval_status == 0 || $proposal_data->approval_status == 1)
        {
            drupal_set_message(t('We have already received your proposal.'), 'status');
            drupal_goto('');
            return;
        } //$proposal_data->approval_status == 0 || $proposal_data->approval_status == 1
    } //$proposal_data
    $form['#attributes'] = array(
        'enctype' => "multipart/form-data"
    );
    $form['name_title'] = array(
        '#type' => 'select',
        '#title' => t('Title'),
        '#options' => array(
            'Dr' => 'Dr.',
            'Prof' => 'Prof.',
            'Shri' => 'Shri',
            'Smt' => 'Smt',
            'Ku.' => 'Ku.',
            'Mr.' => 'Mr.',
            'Mrs.' => 'Mrs.',
            'Ms.' => 'Ms.',
        ),
        '#required' => TRUE
    );
    $form['fname'] = array(
        '#type' => 'textfield',
        '#title' => t('First Name'),
        '#size' => 30,
        '#maxlength' => 50,
        '#required' => TRUE
    );
    $form['lname'] = array(
        '#type' => 'textfield',
        '#title' => t('last Name'),
        '#size' => 30,
        '#maxlength' => 50,
        '#required' => TRUE
    );
    $form['designation'] = array(
        '#type' => 'textfield',
        '#title' => t('Designation'),
        '#size' => 30,
        '#maxlength' => 50,
        '#required' => TRUE
    );
    $form['institute_company'] = array(
        '#type' => 'textfield',
        '#title' => t('Name of the Institute/Company'),
        '#size' => 30,
        '#maxlength' => 50,
        '#required' => TRUE
    );
    $form['email_id'] = array(
        '#type' => 'textfield',
        '#title' => t('Email'),
        '#size' => 30,
        '#value' => $user->mail,
        '#disabled' => TRUE
    );
    $form['alt_email_id'] = array(
        '#type' => 'textfield',
        '#title' => t('Organization Email'),
        '#size' => 30,
        '#value' => $user->mail,
        '#disabled' => False
    );
    $form['contact_ph'] = array(
        '#type' => 'textfield',
        '#title' => t('Contact No.'),
        '#size' => 30,
        '#maxlength' => 15,
        '#required' => TRUE
    );
    $form['department'] = array(
        '#type' => 'select',
        '#title' => t('Department/Branch'),
        //'#options' => _lm_list_of_departments(),
        '#options' => array(""=>""),
        '#required' => TRUE
    );
    $form['university'] = array(
        '#type' => 'textfield',
        '#title' => t('University/ Institute'),
        '#size' => 80,
        '#maxlength' => 200,
        '#required' => TRUE,
        '#attributes' => array(
            'placeholder' => 'Insert full name of your institute/ university.... '
        ),
        '#description' => 'Please insert full name of your institute/ university.'
    );
    $form['city'] = array(
        '#type' => 'select',
        '#title' => t('City/ Village'),
        //'#options' => _lm_list_of_cities(),
        '#options' => array(""=>""),
        '#maxlength' => 150,
        '#required' => TRUE,
        '#description' => 'Please select location of your institute/ university.'
    );
    $form['pincode'] = array(
        '#type' => 'textfield',
        '#title' => t('Pincode'),
        '#size' => 30,
        '#maxlength' => 6,
        '#required' => TRUE,
        '#attributes' => array(
            'placeholder' => 'Insert pincode of your city/ village....'
        ),
        '#description' => 'Please insert pincode of your institute/ university.'
    );
    $form['all_state'] = array(
        '#type' => 'select',
        '#title' => t('State'),
        //'#options' => _lm_list_of_states(),
        '#options' => array(""=>""),
        '#required' => TRUE,
        '#tree' => TRUE,
        '#validated' => TRUE,
        '#description' => 'Please select state of your institute/ university.'
    );
    $form['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Submit')
    );
    return $form;
}
