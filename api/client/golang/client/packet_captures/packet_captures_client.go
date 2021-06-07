// Code generated by go-swagger; DO NOT EDIT.

package packet_captures

// This file was generated by the swagger tool.
// Editing this file might prove futile when you re-run the swagger generate command

import (
	"fmt"
	"io"

	"github.com/go-openapi/runtime"
	"github.com/go-openapi/strfmt"
)

// New creates a new packet captures API client.
func New(transport runtime.ClientTransport, formats strfmt.Registry) ClientService {
	return &Client{transport: transport, formats: formats}
}

/*
Client for packet captures API
*/
type Client struct {
	transport runtime.ClientTransport
	formats   strfmt.Registry
}

// ClientOption is the option for Client methods
type ClientOption func(*runtime.ClientOperation)

// ClientService is the interface for Client methods
type ClientService interface {
	BulkCreatePacketCaptures(params *BulkCreatePacketCapturesParams, opts ...ClientOption) (*BulkCreatePacketCapturesOK, error)

	BulkDeletePacketCaptures(params *BulkDeletePacketCapturesParams, opts ...ClientOption) (*BulkDeletePacketCapturesNoContent, error)

	BulkStartPacketCaptures(params *BulkStartPacketCapturesParams, opts ...ClientOption) (*BulkStartPacketCapturesOK, error)

	BulkStopPacketCaptures(params *BulkStopPacketCapturesParams, opts ...ClientOption) (*BulkStopPacketCapturesNoContent, error)

	CreatePacketCapture(params *CreatePacketCaptureParams, opts ...ClientOption) (*CreatePacketCaptureCreated, error)

	DeletePacketCapture(params *DeletePacketCaptureParams, opts ...ClientOption) (*DeletePacketCaptureNoContent, error)

	DeletePacketCaptureResult(params *DeletePacketCaptureResultParams, opts ...ClientOption) (*DeletePacketCaptureResultNoContent, error)

	DeletePacketCaptureResults(params *DeletePacketCaptureResultsParams, opts ...ClientOption) (*DeletePacketCaptureResultsNoContent, error)

	DeletePacketCaptures(params *DeletePacketCapturesParams, opts ...ClientOption) (*DeletePacketCapturesNoContent, error)

	GetPacketCapture(params *GetPacketCaptureParams, opts ...ClientOption) (*GetPacketCaptureOK, error)

	GetPacketCaptureLive(params *GetPacketCaptureLiveParams, writer io.Writer, opts ...ClientOption) (*GetPacketCaptureLiveOK, error)

	GetPacketCapturePcap(params *GetPacketCapturePcapParams, writer io.Writer, opts ...ClientOption) (*GetPacketCapturePcapOK, error)

	GetPacketCaptureResult(params *GetPacketCaptureResultParams, opts ...ClientOption) (*GetPacketCaptureResultOK, error)

	GetPacketCapturesPcap(params *GetPacketCapturesPcapParams, writer io.Writer, opts ...ClientOption) (*GetPacketCapturesPcapOK, error)

	ListPacketCaptureResults(params *ListPacketCaptureResultsParams, opts ...ClientOption) (*ListPacketCaptureResultsOK, error)

	ListPacketCaptures(params *ListPacketCapturesParams, opts ...ClientOption) (*ListPacketCapturesOK, error)

	StartPacketCapture(params *StartPacketCaptureParams, opts ...ClientOption) (*StartPacketCaptureCreated, error)

	StopPacketCapture(params *StopPacketCaptureParams, opts ...ClientOption) (*StopPacketCaptureNoContent, error)

	SetTransport(transport runtime.ClientTransport)
}

/*
  BulkCreatePacketCaptures bulks create packet captures

  Create multiple packet captures. Requests are processed in an
all-or-nothing manner, i.e. a single capture creation failure
causes all capture creations for this request to fail.

*/
func (a *Client) BulkCreatePacketCaptures(params *BulkCreatePacketCapturesParams, opts ...ClientOption) (*BulkCreatePacketCapturesOK, error) {
	// TODO: Validate the params before sending
	if params == nil {
		params = NewBulkCreatePacketCapturesParams()
	}
	op := &runtime.ClientOperation{
		ID:                 "BulkCreatePacketCaptures",
		Method:             "POST",
		PathPattern:        "/packet/captures/x/bulk-create",
		ProducesMediaTypes: []string{"application/json"},
		ConsumesMediaTypes: []string{"application/json"},
		Schemes:            []string{"http", "https"},
		Params:             params,
		Reader:             &BulkCreatePacketCapturesReader{formats: a.formats},
		Context:            params.Context,
		Client:             params.HTTPClient,
	}
	for _, opt := range opts {
		opt(op)
	}

	result, err := a.transport.Submit(op)
	if err != nil {
		return nil, err
	}
	success, ok := result.(*BulkCreatePacketCapturesOK)
	if ok {
		return success, nil
	}
	// unexpected success response
	// safeguard: normally, absent a default response, unknown success responses return an error above: so this is a codegen issue
	msg := fmt.Sprintf("unexpected success response for BulkCreatePacketCaptures: API contract not enforced by server. Client expected to get an error, but got: %T", result)
	panic(msg)
}

/*
  BulkDeletePacketCaptures bulks delete packet captures

  Delete multiple packet captures in a best-effort manner. Captures
can only be deleted when inactive. Active or Non-existant capture ids
do not cause errors.  Also deletes results and captured packets
associated with the capture. Idempotent.

*/
func (a *Client) BulkDeletePacketCaptures(params *BulkDeletePacketCapturesParams, opts ...ClientOption) (*BulkDeletePacketCapturesNoContent, error) {
	// TODO: Validate the params before sending
	if params == nil {
		params = NewBulkDeletePacketCapturesParams()
	}
	op := &runtime.ClientOperation{
		ID:                 "BulkDeletePacketCaptures",
		Method:             "POST",
		PathPattern:        "/packet/captures/x/bulk-delete",
		ProducesMediaTypes: []string{"application/json"},
		ConsumesMediaTypes: []string{"application/json"},
		Schemes:            []string{"http", "https"},
		Params:             params,
		Reader:             &BulkDeletePacketCapturesReader{formats: a.formats},
		Context:            params.Context,
		Client:             params.HTTPClient,
	}
	for _, opt := range opts {
		opt(op)
	}

	result, err := a.transport.Submit(op)
	if err != nil {
		return nil, err
	}
	success, ok := result.(*BulkDeletePacketCapturesNoContent)
	if ok {
		return success, nil
	}
	// unexpected success response
	// safeguard: normally, absent a default response, unknown success responses return an error above: so this is a codegen issue
	msg := fmt.Sprintf("unexpected success response for BulkDeletePacketCaptures: API contract not enforced by server. Client expected to get an error, but got: %T", result)
	panic(msg)
}

/*
  BulkStartPacketCaptures bulks start packet captures

  Start multiple packet captures simultaneously
*/
func (a *Client) BulkStartPacketCaptures(params *BulkStartPacketCapturesParams, opts ...ClientOption) (*BulkStartPacketCapturesOK, error) {
	// TODO: Validate the params before sending
	if params == nil {
		params = NewBulkStartPacketCapturesParams()
	}
	op := &runtime.ClientOperation{
		ID:                 "BulkStartPacketCaptures",
		Method:             "POST",
		PathPattern:        "/packet/captures/x/bulk-start",
		ProducesMediaTypes: []string{"application/json"},
		ConsumesMediaTypes: []string{"application/json"},
		Schemes:            []string{"http", "https"},
		Params:             params,
		Reader:             &BulkStartPacketCapturesReader{formats: a.formats},
		Context:            params.Context,
		Client:             params.HTTPClient,
	}
	for _, opt := range opts {
		opt(op)
	}

	result, err := a.transport.Submit(op)
	if err != nil {
		return nil, err
	}
	success, ok := result.(*BulkStartPacketCapturesOK)
	if ok {
		return success, nil
	}
	// unexpected success response
	// safeguard: normally, absent a default response, unknown success responses return an error above: so this is a codegen issue
	msg := fmt.Sprintf("unexpected success response for BulkStartPacketCaptures: API contract not enforced by server. Client expected to get an error, but got: %T", result)
	panic(msg)
}

/*
  BulkStopPacketCaptures bulks stop packet captures

  Stop multiple packet captures simultaneously
*/
func (a *Client) BulkStopPacketCaptures(params *BulkStopPacketCapturesParams, opts ...ClientOption) (*BulkStopPacketCapturesNoContent, error) {
	// TODO: Validate the params before sending
	if params == nil {
		params = NewBulkStopPacketCapturesParams()
	}
	op := &runtime.ClientOperation{
		ID:                 "BulkStopPacketCaptures",
		Method:             "POST",
		PathPattern:        "/packet/captures/x/bulk-stop",
		ProducesMediaTypes: []string{"application/json"},
		ConsumesMediaTypes: []string{"application/json"},
		Schemes:            []string{"http", "https"},
		Params:             params,
		Reader:             &BulkStopPacketCapturesReader{formats: a.formats},
		Context:            params.Context,
		Client:             params.HTTPClient,
	}
	for _, opt := range opts {
		opt(op)
	}

	result, err := a.transport.Submit(op)
	if err != nil {
		return nil, err
	}
	success, ok := result.(*BulkStopPacketCapturesNoContent)
	if ok {
		return success, nil
	}
	// unexpected success response
	// safeguard: normally, absent a default response, unknown success responses return an error above: so this is a codegen issue
	msg := fmt.Sprintf("unexpected success response for BulkStopPacketCaptures: API contract not enforced by server. Client expected to get an error, but got: %T", result)
	panic(msg)
}

/*
  CreatePacketCapture creates a packet capture

  Create a new packet capture.
*/
func (a *Client) CreatePacketCapture(params *CreatePacketCaptureParams, opts ...ClientOption) (*CreatePacketCaptureCreated, error) {
	// TODO: Validate the params before sending
	if params == nil {
		params = NewCreatePacketCaptureParams()
	}
	op := &runtime.ClientOperation{
		ID:                 "CreatePacketCapture",
		Method:             "POST",
		PathPattern:        "/packet/captures",
		ProducesMediaTypes: []string{"application/json"},
		ConsumesMediaTypes: []string{"application/json"},
		Schemes:            []string{"http", "https"},
		Params:             params,
		Reader:             &CreatePacketCaptureReader{formats: a.formats},
		Context:            params.Context,
		Client:             params.HTTPClient,
	}
	for _, opt := range opts {
		opt(op)
	}

	result, err := a.transport.Submit(op)
	if err != nil {
		return nil, err
	}
	success, ok := result.(*CreatePacketCaptureCreated)
	if ok {
		return success, nil
	}
	// unexpected success response
	// safeguard: normally, absent a default response, unknown success responses return an error above: so this is a codegen issue
	msg := fmt.Sprintf("unexpected success response for CreatePacketCapture: API contract not enforced by server. Client expected to get an error, but got: %T", result)
	panic(msg)
}

/*
  DeletePacketCapture deletes a packet capture

  Delete a stopped packet capture by id.
Also deletes results and captured packets associated with the capture. Idempotent.

*/
func (a *Client) DeletePacketCapture(params *DeletePacketCaptureParams, opts ...ClientOption) (*DeletePacketCaptureNoContent, error) {
	// TODO: Validate the params before sending
	if params == nil {
		params = NewDeletePacketCaptureParams()
	}
	op := &runtime.ClientOperation{
		ID:                 "DeletePacketCapture",
		Method:             "DELETE",
		PathPattern:        "/packet/captures/{id}",
		ProducesMediaTypes: []string{"application/json"},
		ConsumesMediaTypes: []string{"application/json"},
		Schemes:            []string{"http", "https"},
		Params:             params,
		Reader:             &DeletePacketCaptureReader{formats: a.formats},
		Context:            params.Context,
		Client:             params.HTTPClient,
	}
	for _, opt := range opts {
		opt(op)
	}

	result, err := a.transport.Submit(op)
	if err != nil {
		return nil, err
	}
	success, ok := result.(*DeletePacketCaptureNoContent)
	if ok {
		return success, nil
	}
	// unexpected success response
	// safeguard: normally, absent a default response, unknown success responses return an error above: so this is a codegen issue
	msg := fmt.Sprintf("unexpected success response for DeletePacketCapture: API contract not enforced by server. Client expected to get an error, but got: %T", result)
	panic(msg)
}

/*
  DeletePacketCaptureResult deletes a packet capture result

  Delete an inactive packet capture result.
Also deletes captured packets associated with the results.

*/
func (a *Client) DeletePacketCaptureResult(params *DeletePacketCaptureResultParams, opts ...ClientOption) (*DeletePacketCaptureResultNoContent, error) {
	// TODO: Validate the params before sending
	if params == nil {
		params = NewDeletePacketCaptureResultParams()
	}
	op := &runtime.ClientOperation{
		ID:                 "DeletePacketCaptureResult",
		Method:             "DELETE",
		PathPattern:        "/packet/capture-results/{id}",
		ProducesMediaTypes: []string{"application/json"},
		ConsumesMediaTypes: []string{"application/json"},
		Schemes:            []string{"http", "https"},
		Params:             params,
		Reader:             &DeletePacketCaptureResultReader{formats: a.formats},
		Context:            params.Context,
		Client:             params.HTTPClient,
	}
	for _, opt := range opts {
		opt(op)
	}

	result, err := a.transport.Submit(op)
	if err != nil {
		return nil, err
	}
	success, ok := result.(*DeletePacketCaptureResultNoContent)
	if ok {
		return success, nil
	}
	// unexpected success response
	// safeguard: normally, absent a default response, unknown success responses return an error above: so this is a codegen issue
	msg := fmt.Sprintf("unexpected success response for DeletePacketCaptureResult: API contract not enforced by server. Client expected to get an error, but got: %T", result)
	panic(msg)
}

/*
  DeletePacketCaptureResults deletes all capture results

  Delete all inactive packet capture results. Also deletes captured packets associated with the results.
*/
func (a *Client) DeletePacketCaptureResults(params *DeletePacketCaptureResultsParams, opts ...ClientOption) (*DeletePacketCaptureResultsNoContent, error) {
	// TODO: Validate the params before sending
	if params == nil {
		params = NewDeletePacketCaptureResultsParams()
	}
	op := &runtime.ClientOperation{
		ID:                 "DeletePacketCaptureResults",
		Method:             "DELETE",
		PathPattern:        "/packet/capture-results",
		ProducesMediaTypes: []string{"application/json"},
		ConsumesMediaTypes: []string{"application/json"},
		Schemes:            []string{"http", "https"},
		Params:             params,
		Reader:             &DeletePacketCaptureResultsReader{formats: a.formats},
		Context:            params.Context,
		Client:             params.HTTPClient,
	}
	for _, opt := range opts {
		opt(op)
	}

	result, err := a.transport.Submit(op)
	if err != nil {
		return nil, err
	}
	success, ok := result.(*DeletePacketCaptureResultsNoContent)
	if ok {
		return success, nil
	}
	// unexpected success response
	// safeguard: normally, absent a default response, unknown success responses return an error above: so this is a codegen issue
	msg := fmt.Sprintf("unexpected success response for DeletePacketCaptureResults: API contract not enforced by server. Client expected to get an error, but got: %T", result)
	panic(msg)
}

/*
  DeletePacketCaptures deletes all packet captures

  Delete all inactive packet captures.
Also deletes captured packets and results associated with the capture.  Idempotent.

*/
func (a *Client) DeletePacketCaptures(params *DeletePacketCapturesParams, opts ...ClientOption) (*DeletePacketCapturesNoContent, error) {
	// TODO: Validate the params before sending
	if params == nil {
		params = NewDeletePacketCapturesParams()
	}
	op := &runtime.ClientOperation{
		ID:                 "DeletePacketCaptures",
		Method:             "DELETE",
		PathPattern:        "/packet/captures",
		ProducesMediaTypes: []string{"application/json"},
		ConsumesMediaTypes: []string{"application/json"},
		Schemes:            []string{"http", "https"},
		Params:             params,
		Reader:             &DeletePacketCapturesReader{formats: a.formats},
		Context:            params.Context,
		Client:             params.HTTPClient,
	}
	for _, opt := range opts {
		opt(op)
	}

	result, err := a.transport.Submit(op)
	if err != nil {
		return nil, err
	}
	success, ok := result.(*DeletePacketCapturesNoContent)
	if ok {
		return success, nil
	}
	// unexpected success response
	// safeguard: normally, absent a default response, unknown success responses return an error above: so this is a codegen issue
	msg := fmt.Sprintf("unexpected success response for DeletePacketCaptures: API contract not enforced by server. Client expected to get an error, but got: %T", result)
	panic(msg)
}

/*
  GetPacketCapture gets a packet capture

  Return a packet capture by id.
*/
func (a *Client) GetPacketCapture(params *GetPacketCaptureParams, opts ...ClientOption) (*GetPacketCaptureOK, error) {
	// TODO: Validate the params before sending
	if params == nil {
		params = NewGetPacketCaptureParams()
	}
	op := &runtime.ClientOperation{
		ID:                 "GetPacketCapture",
		Method:             "GET",
		PathPattern:        "/packet/captures/{id}",
		ProducesMediaTypes: []string{"application/json"},
		ConsumesMediaTypes: []string{"application/json"},
		Schemes:            []string{"http", "https"},
		Params:             params,
		Reader:             &GetPacketCaptureReader{formats: a.formats},
		Context:            params.Context,
		Client:             params.HTTPClient,
	}
	for _, opt := range opts {
		opt(op)
	}

	result, err := a.transport.Submit(op)
	if err != nil {
		return nil, err
	}
	success, ok := result.(*GetPacketCaptureOK)
	if ok {
		return success, nil
	}
	// unexpected success response
	// safeguard: normally, absent a default response, unknown success responses return an error above: so this is a codegen issue
	msg := fmt.Sprintf("unexpected success response for GetPacketCapture: API contract not enforced by server. Client expected to get an error, but got: %T", result)
	panic(msg)
}

/*
  GetPacketCaptureLive gets live capture packet data as a pcap file

  Returns a pcap file of the captured data.
*/
func (a *Client) GetPacketCaptureLive(params *GetPacketCaptureLiveParams, writer io.Writer, opts ...ClientOption) (*GetPacketCaptureLiveOK, error) {
	// TODO: Validate the params before sending
	if params == nil {
		params = NewGetPacketCaptureLiveParams()
	}
	op := &runtime.ClientOperation{
		ID:                 "GetPacketCaptureLive",
		Method:             "GET",
		PathPattern:        "/packet/capture-results/{id}/live",
		ProducesMediaTypes: []string{"application/x-pcapng"},
		ConsumesMediaTypes: []string{"application/json"},
		Schemes:            []string{"http", "https"},
		Params:             params,
		Reader:             &GetPacketCaptureLiveReader{formats: a.formats, writer: writer},
		Context:            params.Context,
		Client:             params.HTTPClient,
	}
	for _, opt := range opts {
		opt(op)
	}

	result, err := a.transport.Submit(op)
	if err != nil {
		return nil, err
	}
	success, ok := result.(*GetPacketCaptureLiveOK)
	if ok {
		return success, nil
	}
	// unexpected success response
	// safeguard: normally, absent a default response, unknown success responses return an error above: so this is a codegen issue
	msg := fmt.Sprintf("unexpected success response for GetPacketCaptureLive: API contract not enforced by server. Client expected to get an error, but got: %T", result)
	panic(msg)
}

/*
  GetPacketCapturePcap gets a packet data as a pcap file

  Returns a pcap file of the captured data.
*/
func (a *Client) GetPacketCapturePcap(params *GetPacketCapturePcapParams, writer io.Writer, opts ...ClientOption) (*GetPacketCapturePcapOK, error) {
	// TODO: Validate the params before sending
	if params == nil {
		params = NewGetPacketCapturePcapParams()
	}
	op := &runtime.ClientOperation{
		ID:                 "GetPacketCapturePcap",
		Method:             "GET",
		PathPattern:        "/packet/capture-results/{id}/pcap",
		ProducesMediaTypes: []string{"application/x-pcapng"},
		ConsumesMediaTypes: []string{"application/json"},
		Schemes:            []string{"http", "https"},
		Params:             params,
		Reader:             &GetPacketCapturePcapReader{formats: a.formats, writer: writer},
		Context:            params.Context,
		Client:             params.HTTPClient,
	}
	for _, opt := range opts {
		opt(op)
	}

	result, err := a.transport.Submit(op)
	if err != nil {
		return nil, err
	}
	success, ok := result.(*GetPacketCapturePcapOK)
	if ok {
		return success, nil
	}
	// unexpected success response
	// safeguard: normally, absent a default response, unknown success responses return an error above: so this is a codegen issue
	msg := fmt.Sprintf("unexpected success response for GetPacketCapturePcap: API contract not enforced by server. Client expected to get an error, but got: %T", result)
	panic(msg)
}

/*
  GetPacketCaptureResult gets a packet capture result

  Returns results from a packet capture by result id.
*/
func (a *Client) GetPacketCaptureResult(params *GetPacketCaptureResultParams, opts ...ClientOption) (*GetPacketCaptureResultOK, error) {
	// TODO: Validate the params before sending
	if params == nil {
		params = NewGetPacketCaptureResultParams()
	}
	op := &runtime.ClientOperation{
		ID:                 "GetPacketCaptureResult",
		Method:             "GET",
		PathPattern:        "/packet/capture-results/{id}",
		ProducesMediaTypes: []string{"application/json"},
		ConsumesMediaTypes: []string{"application/json"},
		Schemes:            []string{"http", "https"},
		Params:             params,
		Reader:             &GetPacketCaptureResultReader{formats: a.formats},
		Context:            params.Context,
		Client:             params.HTTPClient,
	}
	for _, opt := range opts {
		opt(op)
	}

	result, err := a.transport.Submit(op)
	if err != nil {
		return nil, err
	}
	success, ok := result.(*GetPacketCaptureResultOK)
	if ok {
		return success, nil
	}
	// unexpected success response
	// safeguard: normally, absent a default response, unknown success responses return an error above: so this is a codegen issue
	msg := fmt.Sprintf("unexpected success response for GetPacketCaptureResult: API contract not enforced by server. Client expected to get an error, but got: %T", result)
	panic(msg)
}

/*
  GetPacketCapturesPcap gets merged packet data from multiple captures

  Get merged packet data from multiple captures as a pcap file
*/
func (a *Client) GetPacketCapturesPcap(params *GetPacketCapturesPcapParams, writer io.Writer, opts ...ClientOption) (*GetPacketCapturesPcapOK, error) {
	// TODO: Validate the params before sending
	if params == nil {
		params = NewGetPacketCapturesPcapParams()
	}
	op := &runtime.ClientOperation{
		ID:                 "GetPacketCapturesPcap",
		Method:             "POST",
		PathPattern:        "/packet/captures/x/merge",
		ProducesMediaTypes: []string{"application/x-pcapng"},
		ConsumesMediaTypes: []string{"application/json"},
		Schemes:            []string{"http", "https"},
		Params:             params,
		Reader:             &GetPacketCapturesPcapReader{formats: a.formats, writer: writer},
		Context:            params.Context,
		Client:             params.HTTPClient,
	}
	for _, opt := range opts {
		opt(op)
	}

	result, err := a.transport.Submit(op)
	if err != nil {
		return nil, err
	}
	success, ok := result.(*GetPacketCapturesPcapOK)
	if ok {
		return success, nil
	}
	// unexpected success response
	// safeguard: normally, absent a default response, unknown success responses return an error above: so this is a codegen issue
	msg := fmt.Sprintf("unexpected success response for GetPacketCapturesPcap: API contract not enforced by server. Client expected to get an error, but got: %T", result)
	panic(msg)
}

/*
  ListPacketCaptureResults lists capture results

  The `capture-results` endpoint returns all capture results created
by capture instances.

*/
func (a *Client) ListPacketCaptureResults(params *ListPacketCaptureResultsParams, opts ...ClientOption) (*ListPacketCaptureResultsOK, error) {
	// TODO: Validate the params before sending
	if params == nil {
		params = NewListPacketCaptureResultsParams()
	}
	op := &runtime.ClientOperation{
		ID:                 "ListPacketCaptureResults",
		Method:             "GET",
		PathPattern:        "/packet/capture-results",
		ProducesMediaTypes: []string{"application/json"},
		ConsumesMediaTypes: []string{"application/json"},
		Schemes:            []string{"http", "https"},
		Params:             params,
		Reader:             &ListPacketCaptureResultsReader{formats: a.formats},
		Context:            params.Context,
		Client:             params.HTTPClient,
	}
	for _, opt := range opts {
		opt(op)
	}

	result, err := a.transport.Submit(op)
	if err != nil {
		return nil, err
	}
	success, ok := result.(*ListPacketCaptureResultsOK)
	if ok {
		return success, nil
	}
	// unexpected success response
	// safeguard: normally, absent a default response, unknown success responses return an error above: so this is a codegen issue
	msg := fmt.Sprintf("unexpected success response for ListPacketCaptureResults: API contract not enforced by server. Client expected to get an error, but got: %T", result)
	panic(msg)
}

/*
  ListPacketCaptures lists packet capture

  The `captures` endpoint returns all configured packet captures.

*/
func (a *Client) ListPacketCaptures(params *ListPacketCapturesParams, opts ...ClientOption) (*ListPacketCapturesOK, error) {
	// TODO: Validate the params before sending
	if params == nil {
		params = NewListPacketCapturesParams()
	}
	op := &runtime.ClientOperation{
		ID:                 "ListPacketCaptures",
		Method:             "GET",
		PathPattern:        "/packet/captures",
		ProducesMediaTypes: []string{"application/json"},
		ConsumesMediaTypes: []string{"application/json"},
		Schemes:            []string{"http", "https"},
		Params:             params,
		Reader:             &ListPacketCapturesReader{formats: a.formats},
		Context:            params.Context,
		Client:             params.HTTPClient,
	}
	for _, opt := range opts {
		opt(op)
	}

	result, err := a.transport.Submit(op)
	if err != nil {
		return nil, err
	}
	success, ok := result.(*ListPacketCapturesOK)
	if ok {
		return success, nil
	}
	// unexpected success response
	// safeguard: normally, absent a default response, unknown success responses return an error above: so this is a codegen issue
	msg := fmt.Sprintf("unexpected success response for ListPacketCaptures: API contract not enforced by server. Client expected to get an error, but got: %T", result)
	panic(msg)
}

/*
  StartPacketCapture starts packet capture

  Used to start a non-running capture. Creates a new capture.
result on success.

*/
func (a *Client) StartPacketCapture(params *StartPacketCaptureParams, opts ...ClientOption) (*StartPacketCaptureCreated, error) {
	// TODO: Validate the params before sending
	if params == nil {
		params = NewStartPacketCaptureParams()
	}
	op := &runtime.ClientOperation{
		ID:                 "StartPacketCapture",
		Method:             "POST",
		PathPattern:        "/packet/captures/{id}/start",
		ProducesMediaTypes: []string{"application/json"},
		ConsumesMediaTypes: []string{"application/json"},
		Schemes:            []string{"http", "https"},
		Params:             params,
		Reader:             &StartPacketCaptureReader{formats: a.formats},
		Context:            params.Context,
		Client:             params.HTTPClient,
	}
	for _, opt := range opts {
		opt(op)
	}

	result, err := a.transport.Submit(op)
	if err != nil {
		return nil, err
	}
	success, ok := result.(*StartPacketCaptureCreated)
	if ok {
		return success, nil
	}
	// unexpected success response
	// safeguard: normally, absent a default response, unknown success responses return an error above: so this is a codegen issue
	msg := fmt.Sprintf("unexpected success response for StartPacketCapture: API contract not enforced by server. Client expected to get an error, but got: %T", result)
	panic(msg)
}

/*
  StopPacketCapture stops packet capture

  Use to halt a running capture. Idempotent.
*/
func (a *Client) StopPacketCapture(params *StopPacketCaptureParams, opts ...ClientOption) (*StopPacketCaptureNoContent, error) {
	// TODO: Validate the params before sending
	if params == nil {
		params = NewStopPacketCaptureParams()
	}
	op := &runtime.ClientOperation{
		ID:                 "StopPacketCapture",
		Method:             "POST",
		PathPattern:        "/packet/captures/{id}/stop",
		ProducesMediaTypes: []string{"application/json"},
		ConsumesMediaTypes: []string{"application/json"},
		Schemes:            []string{"http", "https"},
		Params:             params,
		Reader:             &StopPacketCaptureReader{formats: a.formats},
		Context:            params.Context,
		Client:             params.HTTPClient,
	}
	for _, opt := range opts {
		opt(op)
	}

	result, err := a.transport.Submit(op)
	if err != nil {
		return nil, err
	}
	success, ok := result.(*StopPacketCaptureNoContent)
	if ok {
		return success, nil
	}
	// unexpected success response
	// safeguard: normally, absent a default response, unknown success responses return an error above: so this is a codegen issue
	msg := fmt.Sprintf("unexpected success response for StopPacketCapture: API contract not enforced by server. Client expected to get an error, but got: %T", result)
	panic(msg)
}

// SetTransport changes the transport on the client
func (a *Client) SetTransport(transport runtime.ClientTransport) {
	a.transport = transport
}