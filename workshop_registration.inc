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
  /*  if ($proposal_data)
    {
        if ($proposal_data->approval_status == 0 || $proposal_data->approval_status == 1)
        {
            drupal_set_message(t('We have already received your proposal.'), 'status');
            drupal_goto('');
            return;
        } //$proposal_data->approval_status == 0 || $proposal_data->approval_status == 1
    } //$proposal_data*/
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
    $form['personal_info']['contact_no'] = array(
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
    $form['organization_info']['all_state'] = array(
        '#type' => 'select',
        '#title' => t('State'),
        '#options' => osdag_workshop_booking_list_of_states(),
        '#validated' => TRUE,
        '#states' => array(
            'visible' => array(
                ':input[name="country"]' => array(
                    'value' => 'India'
                )
            )
        )
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
    $cur_year = date("Y");
    $form['workshop_info']['checklist_group']['suggested_date']['start_date'] = array(
        '#type' => 'date_popup',
        '#title' => t('From Date:'),
        '#date_label_position' => '',
        '#description' => '',
        '#default_value' => '',
        '#date_format' => 'Y-m-d',
        '#date_increment' => 0,
        '#date_year_range' => $cur_year.':+0',
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
        '#date_year_range' => $cur_year.':+0',
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
    $form['term_and_conditions'] = array(
        '#type' => 'checkboxes',
        '#title' => t('Terms And Conditions'),
        '#options' => array(
            'status' => t('<a href="term-and-conditions" target="_blank">I agree to the Terms and Conditions</a>')
        ),
        '#required' => TRUE
    );
    $form['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Submit')
    );
    return $form;
}

function osdag_workshop_booking_form_validate($form, &$form_state)
{
    $v = $form_state['values'];
    if (!preg_match('/^[a-zA-Z \.]*$/', $v['personal_info']['fname']))
        form_set_error('fname', t('Allowed only characters'));
    if (!preg_match('/^[a-zA-Z \.]*$/', $v['personal_info']['lname']))
        form_set_error('lname', t('Allowed only characters'));
    if (!preg_match('/^[0-9\ \+]{0,15}$/', $v['personal_info']['contact_no']))
        form_set_error('contact_no', t('Invalid contact number'));
    if (!preg_match('/^[a-zA-Z \.]*$/', $v['personal_info']['designation']))
        form_set_error('designation', t('Allowed only characters'));
    if(strlen($v['organization_info']['institute_company']) < 0 || $v['organization_info']['institute_company'] > 30)
        form_set_error('institute_company', t('Institute/company name length is invalid'));
    if(strlen($v['organization_info']['institute_company_address']) < 10 ||
    strlen($v['organization_info']['institute_company_address']) > 100){
        $v['organization_info']['institute_company_address'] = trim($v['organization_info']['institute_company_address']);
        }else{
            form_set_error('institute_company_address', t('Address length is invalid'));
        }
    if($v['workshop_type']['participant_type'] == "Others"){
        if(trim($v['if_others']) == ""){
            form_set_error('if_others', t('Please specify others'));
        }
    }
    if($v['workshop_type']['checklist_group']['available_computer'] =="Yes"){
        if(trim($v['workshop_type']['checklist_group']['if_yes_1']) == ""){
            form_set_error('if_yes_1', t('Please enter value'));
        }
        if($v['workshop_type']['checklist_group']['if_yes_2'] == ""){
            form_set_error('if_yes_2', t('Please select'));
        }
        if($v['workshop_type']['checklist_group']['if_yes_3'] == ""){
            form_set_error('if_yes_3', t('Please select'));
        }
    }
    if($v['workshop_type']['checklist_group']['available_computer'] =="No"){
        if($v['workshop_type']['checklist_group']['if_no_1'] == ""){
            form_set_error('if_yes_1', t('Please select'));
        }
        if($v['workshop_type']['checklist_group']['if_no_2'] == ""){
            form_set_error('if_yes_2', t('Please select'));
        }
    }
    if (!preg_match('/^[0-9]{0,2}$/', $form_state['values']['volunteers']))
        form_set_error('volunteers', t('Invalid number of volunteer'));
}

function osdag_workshop_booking_form_submit($form, &$form_state)
{
    global $user;
    $v = $form_state['values'];
    $query = "INSERT INTO 'osdag_workshop_booking_proposal' ('uid', 'title',
            'fname', 'lname', 'designation', 'email_id', 'contact_no',
            'institute_company', 'address_of_institute_company', 'org_email',
            'city_district', 'indian_state', 'pincode', 'workshop_type',
            'exp_number_of_participent', 'participant_type', 'if_others',
            'available_computer', 'if_yes_1', 'if_yes_2', 'if_yes_3', 'if_no_1',
            'if_no_2', 'volunteers', 'from_w_date', 'end_w_date',
            'travel_arrangement', 'how_did_you_here')
            VALUES(
            ':uid', ':title', ':fname', ':lname', ':designation', ':email_id',
            ':contact_no', ':institute_company',
            ':address_of_institute_company',':org_email', ':city_district',
            ':indian_state', ':pincode', ':workshop_type',
            ':exp_number_of_participent', ':participant_type', ':if_others',
            ':available_computer', ':if_yes_1', ':if_yes_2', ':if_yes_3',
            ':if_no_1', ':if_no_2', ':volunteers', ':from_w_date',
            ':end_w_date', ':travel_arrangement', ':how_did_you_here')";

    $args = array(
        ':uid' => $user->uid,
        ':title' => $v['name_title'],
        ':fname' => $v['fname'],
        ':lname' => $v['lname'],
        ':designation' => $v['designation'],
        ':email_id' => $v['email_id'],
        ':contact_no' => $v['contact_no'],
        ':institute_company' => $v['institute_company'],
        ':address_of_institute_company' => $v['institute_company_address'],
        ':org_email' => $v['alt_email_id'],
        ':city_district' => $v['city_district'],
        ':indian_state' => $v['all_state'],
        ':pincode' => $v['pincode'],
        ':workshop_type' => $v['workshop_type'],
        ':exp_number_of_participent' => $v['expected_number_of_participants'],
        ':participant_type' => $v['participant_type'],
        ':if_others' => $v['if_others'],
        ':available_computer' => $v['available_computer'],
        ':if_yes_1' => $v['if_yes_1'],
        ':if_yes_2' => $v['if_yes_2'],
        ':if_yes_3' => $v['if_yes_3'],
        ':if_no_1' => $v['if_no_1'],
        ':if_no_2' => $v['if_no_2'],
        ':volunteers' => $v['volunteers'],
        ':from_w_date' => $v['start_date'],
        ':end_w_date' => $v['end_date'],
        ':travel_arrangement' => $v['travel_arrangement'],
        ':how_did_you_here' => $v['how_did_you_here'],
    );
        $result = db_query($query, $args, array(
            'return' => Database::RETURN_INSERT_ID
        ));
        /* sending email */
    $email_to = $user->mail;
    $from = variable_get('osdag_workshop_booking_from_email', '');
    $bcc = variable_get('osdag_workshop_booking_bcc_emails', '');
    $cc = variable_get('osdag_workshop_booking_cc_emails', '');
    $params['proposal_received']['proposal_id'] = $proposal_id;
    $params['proposal_received']['user_id'] = $user->uid;
    $params['proposal_received']['headers'] = array(
        'From' => $from,
        'MIME-Version' => '1.0',
        'Content-Type' => 'text/plain; charset=UTF-8; format=flowed; delsp=yes',
        'Content-Transfer-Encoding' => '8Bit',
        'X-Mailer' => 'Drupal',
        'Cc' => $cc,
        'Bcc' => $bcc
    );
    if (!drupal_mail('osdag_workshop_booking', 'proposal_received', $email_to, language_default(), $params, $from, TRUE))
        drupal_set_message('Error sending email message.', 'error');
    drupal_set_message(t('We have received you osdag workshop proposal. We will get back to you soon.'), 'status');
    drupal_goto('');
}
