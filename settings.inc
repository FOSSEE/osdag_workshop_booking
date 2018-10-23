<?php
// $Id$
function osdag_workshop_booking_settings_form($form, &$form_state)
{
    $form['from_email'] = array(
        '#type' => 'textfield',
        '#title' => t('Outgoing from email address From mail'),
        '#description' => t('Email address to be display in the from field of all outgoing messages'),
        '#size' => 50,
        '#maxlength' => 255,
        '#required' => TRUE,
        '#default_value' => variable_get('osdag_workshop_booking_from_email', '')
    );
    $form['cc_email'] = array(
        '#type' => 'textfield',
        '#title' => t('Notification emails CC'),
        '#description' => t('A comma separated list of email addresses to receive notifications emails'),
        '#size' => 50,
        '#maxlength' => 255,
        '#required' => TRUE,
        '#default_value' => variable_get('osdag_workshop_booking_cc_emails', '')
    );
    $form['bcc_email'] = array(
        '#type' => 'textfield',
        '#title' => t('Notification emails of BCC'),
        '#description' => t('A comma separated list of email addresses to receive notifications emails'),
        '#size' => 50,
        '#maxlength' => 255,
        '#required' => TRUE,
        '#default_value' => variable_get('osdag_workshop_booking_bcc_emails', '')
    );
    $form['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Submit')
    );
    return $form;
}
function osdag_workshop_booking_settings_form_validate($form, &$form_state)
{
    return;
}
function osdag_workshop_booking_settings_form_submit($form, &$form_state)
{
    variable_set('osdag_workshop_booking_cc_emails', $form_state['values']['cc_email']);
    variable_set('osdag_workshop_booking_from_email', $form_state['values']['from_email']);
    variable_set('osdag_workshop_booking_bcc_emails', $form_state['values']['bcc_email']);
    drupal_set_message(t('Settings updated'), 'status');
}
