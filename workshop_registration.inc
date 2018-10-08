<?php
/* workshop booking registration form */
function osdag_workshop_booking_form($form, &$form_state)
{
    global $user;
    /************************ start approve book details ************************/
    $query = db_select('osdag_workshop_booking_proposal');
    $query->fields('osdag_workshop_booking_proposal');
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
    $form['personal_info'] = array(
        '#type' => 'fieldset',
        '#title' => t('Personal Information'),
        '#tree' => TRUE,
    );
    $form['personal_info']['name_title'] = array(
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
    $form['personal_info']['fname'] = array(
        '#type' => 'textfield',
        '#title' => t('First Name'),
        '#size' => 30,
        '#maxlength' => 50,
        '#required' => TRUE
    );
    $form['personal_info']['lname'] = array(
        '#type' => 'textfield',
        '#title' => t('last Name'),
        '#size' => 30,
        '#maxlength' => 50,
        '#required' => TRUE
    );
    $form['personal_info']['designation'] = array(
        '#type' => 'textfield',
        '#title' => t('Designation'),
        '#size' => 30,
        '#maxlength' => 50,
        '#required' => TRUE
    );
    $form['personal_info']['email_id'] = array(
        '#type' => 'textfield',
        '#title' => t('Email'),
        '#size' => 30,
        '#value' => $user->mail,
        '#disabled' => TRUE
    );
    $form['personal_info']['contact_ph'] = array(
        '#type' => 'textfield',
        '#title' => t('Contact No.'),
        '#size' => 30,
        '#maxlength' => 15,
        '#required' => TRUE
    );
    $form['organization_info'] = array(
        '#type' => 'fieldset',
        '#title' => t('Organization Information'),
        '#tree' => TRUE,
    );
    $form['organization_info']['institute_company'] = array(
        '#type' => 'textfield',
        '#title' => t('Name of the Institute/Company'),
        '#size' => 30,
        '#maxlength' => 50,
        '#required' => TRUE
    );
    $form['organization_info']['alt_email_id'] = array(
        '#type' => 'textfield',
        '#title' => t('Official (Institute/Company) Email address'),
        '#size' => 50,
        '#value' => '',
        '#disabled' => False
    );
    $form['organization_info']['institute_company_address'] = array(
        '#type' => 'textarea',
        '#title' => t('Address of the Institute/Company'),
        '#size' => 50,
        '#maxlength' => 50,
        '#required' => TRUE
    );
    $form['organization_info']['city_district'] = array(
        '#type' => 'textfield',
        '#title' => t('City/District'),
        '#size' => 30,
        '#maxlength' => 50,
        '#required' => TRUE
    );
    $form['organization_info']['pincode'] = array(
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
    $form['workshop_info'] = array(
        '#type' => 'fieldset',
        '#title' => t('Workshop Information'),
        '#tree' => TRUE,
    );
    $form['workshop_info']['workshop_type'] = array(
        '#type' => 'select',
        '#title' => t('Workshop type'),
        '#options' => array("1-day training workshop" => "1-day training workshop",
        "2-day training workshop" => "2-day training workshop"),
        '#required' => TRUE
    );
    $form['workshop_info']['expected_number_of_participants'] = array(
        '#type' => 'select',
        '#title' => t('Expected number of participants'),
        '#options' => array("0 to 30" => "0 to 30",
                            "30 to 60" => "30 to 60"),
        '#description' => "[If the number of participants is more than 60 then request for a new workshop for the next batch of 60 students]",
        '#required' => TRUE
    );
    $form['workshop_info']['participant_type'] = array(
        '#type' => 'checkboxes',
        '#title' => t('Participant type'),
        '#options' => array("Undergraduate students" => "Undergraduate students",
                            "Postgraduate students" => "Postgraduate students",
                            "College teachers" => "College teachers",
                            "Design engineers" => "Design engineers",
                            "Site engineers" => "Site engineers",
                            "Others" => "Others"),
        '#description' => "[If others specify]",
        '#required' => TRUE
    );
    $form['workshop_info']['if_others'] = array(
        '#type' => 'textfield',
        '#size' => 30,
        '#maxlength' => 30,
        '#required' => TRUE,
        '#states' => array(
                'visible' => array(
                    ':input[name="workshop_info[participant_type][Others]"]' => array(
                        array('checked' => True),
                    )
                )
        ),
    );
    $form['workshop_info']['checklist_group'] = array(
        '#type' => 'fieldset',
        '#title' => t('Workshop Checklist'),
        '#tree' => TRUE,
    );
    $form['workshop_info']['checklist_group']['is_computer_lab_available'] = array(
        '#type' => 'select',
        '#title' => t('Is a computer lab available at the organizing institute/company?'),
        '#options' => array("Yes" => "Yes",
                            "No" => "No"),
        '#required' => TRUE
    );
    $form['workshop_info']['checklist_group']['if_yes_1'] = array(
        '#type' => 'textfield',
        '#title' => t('What is the Operating system (Windows, Linux etc.) [mention OS with configuration. Ex. Windows 10 or Ubuntu 18.04 etc]'),
        '#size' => 50,
        '#maxlength' => 50,
        '#states' => array(
            'visible' => array(
                ':input[name="workshop_info[checklist_group][is_computer_lab_available]"]' =>
                    array("value" => "Yes"),
            )
        ),
        '#default_value' => '',
        '#required' => TRUE
    );
    $form['workshop_info']['checklist_group']['if_yes_2'] = array(
        '#type' => 'select',
        '#title' => t('Is there a projection facility at the computer lab?'),
        '#options' => array("Yes" => "Yes",
                            "No" => "No"),
        '#states' => array(
            'visible' => array(
                ':input[name="workshop_info[checklist_group][is_computer_lab_available]"]' => 
                    array('value' => 'Yes'),
            )
        ),
        '#default_value' => '',
        '#required' => TRUE
    );
    $form['workshop_info']['checklist_group']['if_yes_3'] = array(
        '#type' => 'select',
        '#title' => t('Are all the computers connected to the Internet?'),
        '#options' => array("Yes" => "Yes",
                            "No" => "No"),
        '#states' => array(
            'visible' => array(
                ':input[name="workshop_info[checklist_group][is_computer_lab_available]"]' => array('value' => 'Yes'),
            )
        ),
        '#default_value' => '',
        '#required' => TRUE
    );
    $form['workshop_info']['checklist_group']['if_no_1'] = array(
        '#type' => 'select',
        '#title' => t('Every participant has to have an individual computer with Osdag pre-installed in it.'),
        '#options' => array("Agree" => "Agree",
                            "Disagree" => "Disagree"),
        '#states' => array(
            'visible' => array(
                ':input[name="workshop_info[checklist_group][is_computer_lab_available]"]' => array('value' => 'No'),
            )
        ),
        '#default_value' => '',
        '#required' => TRUE
    );
    $form['workshop_info']['checklist_group']['if_no_1'] = array(
        '#type' => 'select',
        '#title' => t('All the participants should be accommodated in a single room with audio-visual projection facilities.'),
        '#options' => array("Agree" => "Agree",
                            "Disagree" => "Disagree"),
        '#states' => array(
            'visible' => array(
                ':input[name="workshop_info[checklist_group][is_computer_lab_available]"]' => array('value' => 'No'),
            )
        ),
        '#default_value' => '',
        '#required' => TRUE
    );
    $form['workshop_info']['volunteers'] = array(
        '#type' => 'textfield',
        '#title' => t('Volunteers'),
        '#size' => 30,
        '#maxlength' => 6,
        '#required' => TRUE,
        '#attributes' => array(
            'placeholder' => 'Enter the number of volunteer....'
        ),
        '#description' => '(1 volunteer per 15 participants with a minimum of 2)'
    );
    $form['workshop_info']['checklist_group']['suggested_date'] = array(
        '#type' => 'fieldset',
        '#title' => t('Suggested Date(s)'),
        '#tree' => TRUE,
    );
    $form['workshop_info']['checklist_group']['suggested_date']['start_date'] = array(
        '#type' => 'date_popup',
        '#title' => t('From Date:'),
        '#date_label_position' => '',
        '#description' => '',
        '#default_value' => '',
        '#date_format' => 'Y-m-d',
        '#date_increment' => 0,
        '#date_year_range' => '2011:+0',
        '#datepicker_options' => array(
            'maxDate' => 0
        ),
    );
    $form['workshop_info']['checklist_group']['suggested_date']['end_date'] = array(
        '#type' => 'date_popup',
        '#title' => t('To Date:'),
        '#date_label_position' => '',
        '#description' => '',
        '#default_value' => '',
        '#date_format' => 'Y-m-d',
        '#date_increment' => 0,
        '#date_year_range' => '2011:+0',
        '#datepicker_options' => array(
            'maxDate' => 0
        ),
    );
    $form['workshop_info']['proposed_travel_arrangement'] = array(
        '#type' => 'textarea',
        '#title' => t('What is the proposed travel arrangement for the Osdag resource people'),
        '#size' => 30,
        '#maxlength' => 6,
        '#required' => TRUE,
        '#attributes' => array(
            'placeholder' => 'Enter the proposed travel arrangement for the Osdag resource people....'
        ),
    );
    $form['workshop_info']['how_did_you_here'] = array(
        '#type' => 'select',
        '#title' => t('How did you hear about Osdag training workshop?'),
        '#options' => array("FOSSEE/Osdag Email/website" => "FOSSEE/Osdag Email/website",
                            "FOSSEE/Osdag banner, brochure etc." => "FOSSEE/Osdag banner, brochure etc.",
                            "Web search" => "Web search",
                            "From another college" => "From another college",
                            "Word of mouth" => "Word of mouths"),
        '#required' => TRUE
    );
    $form['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Submit')
    );
    return $form;
}
