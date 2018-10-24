<?php
/**
 * Implementation of hook_mail().
 */
 /**
 * Modify the drupal mail system to send HTML emails.
 */
class WorkshopMailSystem implements MailSystemInterface {
  /**
   * Concatenate and wrap the e-mail body for plain-text mails.
   *
   * @param array $message
   *   A message array, as described in hook_mail_alter().
   *
   * @return array
   *   The formatted $message.
   */
  public function format(array $message) {
    $message['body'] = implode("\n\n", $message['body']);
    return $message;
  }

  /**
   * Send an e-mail message, using Drupal variables and default settings.
   *
   * @see http://php.net/manual/en/function.mail.php
   * @see drupal_mail()
   *
   * @param array $message
   *   A message array, as described in hook_mail_alter().
   *
   * @return bool
   *   TRUE if the mail was successfully accepted, otherwise FALSE.
   */
  public function mail(array $message) {
    $mimeheaders = array();
    foreach ($message['headers'] as $name => $value) {
      $mimeheaders[] = $name . ': ' . mime_header_encode($value);
    }
    $line_endings = variable_get('mail_line_endings', MAIL_LINE_ENDINGS);
    return mail(
      $message['to'],
      mime_header_encode($message['subject']),
      // Note: e-mail uses CRLF for line-endings. PHP's API requires LF
      // on Unix and CRLF on Windows. Drupal automatically guesses the
      // line-ending format appropriate for your system. If you need to
      // override this, adjust $conf['mail_line_endings'] in settings.php.
      preg_replace('@\r?\n@', $line_endings, $message['body']),
      // For headers, PHP's API suggests that we use CRLF normally,
      // but some MTAs incorrectly replace LF with CRLF. See #234403.
      implode("\n", $mimeheaders)
    );
  }
}

function osdag_workshop_booking_mail($key, &$message, $params)
{
    global $user;
    $language = $message['language'];
    switch ($key)
    {
        case 'proposal_received':
            /* initializing data */
            $proposal_q = db_query("SELECT * FROM {osdag_workshop_booking_proposal} WHERE id = :proposal_id LIMIT 1", array( ':proposal_id' => $params['proposal_received']['proposal_id']));
            $proposal_data = $proposal_q->fetchObject();
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

<p>Thank you for showing your interest to organize a '. $workshop_type .' on
 structural steel design and detailing using Open Steel Design and Graphics
 (Osdag) at '. $institute_company .' on '. $suggested_date .'</p>

<p>Your request has been received and is awaiting for approval by PI of Osdag.
 You will get a confirmation email on approval/disapproval/re-scheduling of the
 training workshop within 15 days.</p>

<p>Please note: Unless you get a confirmation email for this workshop with the
 list of instructions, your workshop shall be on the waiting list.</p>


Thank you!

Best Regards,<br>
Team Osdag,<br>
FOSSEE, IIT Bombay.<br>

<p><center><h6>This is an automated system generated email.</h6></center></p>
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
            $proposal_q = db_query("SELECT * FROM {osdag_workshop_booking_proposal} WHERE id = :proposal_id LIMIT 1", array(':proposal_id' => $params['proposal_approved']['proposal_id']));
            $proposal_data = $proposal_q->fetchObject();
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

<p>Your request for organizing the training workshop has been approved by PI of
 Osdag.</p>

<p>The details of the workshop are as follows:
<ul>
<li>'. $workshop_type .'</li>
<li>Date: '. $suggested_date .'</li>
<li>Resource person: One resource person for every 25 participants, with a
 minimum of 2.</li>
</ul>
You will receive an email from team Osdag with detailed Instructions soon.</p>

<p>Thank you!</p>

Best Regards,<br>
Team Osdag,<br>
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
            $proposal_q = db_query("SELECT * FROM {osdag_workshop_booking_proposal} WHERE id = :proposal_id LIMIT 1", array(':proposal_id' => $params['proposal_disapproved']['proposal_id']));
            $proposal_data = $proposal_q->fetchObject();
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

<p>We regret to inform you that your request for organizing the training workshop has been disapproved by PI of Osdag due to '. $proposal_data->disapprove_message .'.</p>


Thank you!

Best Regards,<br>
Team Osdag,<br>
FOSSEE, IIT Bombay.<br>
'
, array(
                    '!site_name' => variable_get('site_name', ''),
                    '!user_name' => $user_data->name
                ), array(
                    'language' => $language->language
                ))
            );
            break;
    }
}
